/*

Allocation mechanism for RAM_G.

*/

#include "Ft_Esd.h"
#include "Ft_Esd_GpuAlloc.h"

#include "FT_Platform.h"
#include "FT_Gpu.h"

#ifdef ESD_SIMULATION
static int s_ErrorGpuAllocFailed = 0;
#endif

void Ft_Esd_GpuAlloc_Reset(Ft_Esd_GpuAlloc *ga)
{
#ifdef ESD_SIMULATION
	s_ErrorGpuAllocFailed = 0;
#endif

	for (int id = 0; id < MAX_NUM_ALLOCATIONS; ++id)
	{
		ga->AllocRefs[id].Idx = MAX_NUM_ALLOCATIONS;
		++ga->AllocRefs[id].Seq; // Seq is always cycled, initial value not important
	}

	for (int idx = 0; idx < MAX_NUM_ALLOCATIONS; ++idx)
	{
		ga->AllocEntries[idx].Address = RAM_G_SIZE;
		ga->AllocEntries[idx].Length = 0;
		ga->AllocEntries[idx].Id = MAX_NUM_ALLOCATIONS;
		ga->AllocEntries[idx].Flags = 0;
	}

	// First allocation entry is unallocated entry of entire RAM_G_SIZE
	ga->AllocEntries[0].Address = 0;
	ga->AllocEntries[0].Length = RAM_G_SIZE;
	ga->NbAllocEntries = 1;
}

void Ft_Esd_GpuAlloc_InsertFree(Ft_Esd_GpuAlloc *ga, ft_uint32_t atidx, ft_uint32_t size)
{
	// First move entries one step forward
	for (int idx = (ga->NbAllocEntries - 1); idx >= atidx; --idx)
	{
		int id = ga->AllocEntries[idx].Id;
		if (id < MAX_NUM_ALLOCATIONS)
		{
			// Move reference idx one ahead
			++ga->AllocRefs[id].Idx;
		}
		ga->AllocEntries[idx + 1] = ga->AllocEntries[idx];
	}

	// Set the free space entry
	ga->AllocEntries[atidx].Address = ga->AllocEntries[atidx - 1].Address + ga->AllocEntries[atidx - 1].Length;
	ga->AllocEntries[atidx].Length = size;
	ga->AllocEntries[atidx].Id = MAX_NUM_ALLOCATIONS;
	ga->AllocEntries[atidx].Flags = 0;
	++ga->NbAllocEntries;
}

Ft_Esd_GpuHandle Ft_Esd_GpuAlloc_Alloc(Ft_Esd_GpuAlloc *ga, ft_uint32_t size, ft_uint16_t flags)
{
	if (ga->NbAllocEntries >= MAX_NUM_ALLOCATIONS)
	{
		goto ReturnInvalidHandle;
	}

	// Always align size to 4 bytes
	size = (size + 3UL) & ~3UL;

	// Scan through the AllocEntries, find the first open allocation that is large enough
	for (int idx = 0; idx < ga->NbAllocEntries; ++idx)
	{
		// Check if allocation entry is unallocated and large enough
		if (ga->AllocEntries[idx].Id == MAX_NUM_ALLOCATIONS
			&& ga->AllocEntries[idx].Length >= size)
		{
			// Find an unused handle
			for (int id = 0; id < MAX_NUM_ALLOCATIONS; ++id)
			{
				if (ga->AllocRefs[id].Idx == MAX_NUM_ALLOCATIONS)
				{
					// Allocate this block
					ft_uint32_t remaining = ga->AllocEntries[idx].Length - size;
					ga->AllocEntries[idx].Length = size;
					ga->AllocEntries[idx].Id = id;
					flags |= GA_USED_FLAG;
					ga->AllocEntries[idx].Flags = flags;
					ga->AllocRefs[id].Idx = idx;
					++ga->AllocRefs[id].Seq;

					// Insert free space entry after
					if (remaining)
					{
						Ft_Esd_GpuAlloc_InsertFree(ga, idx + 1, remaining);
					}

#ifdef ESD_SIMULATION
					s_ErrorGpuAllocFailed = 0;
#endif

					// ESD_print("Alloc id %i\n", id);

					// Return the valid gpu ram handle
					return (Ft_Esd_GpuHandle) {
						.Id = id,
						.Seq = ga->AllocRefs[id].Seq
					};
				}
			}

			// No invalid handle found
			goto ReturnInvalidHandle;
		}
	}

	// No space left, return an invalid allocation handle...
ReturnInvalidHandle:

#ifdef ESD_SIMULATION
	if (!s_ErrorGpuAllocFailed)
	{
		Ft_Esd_LogError("Unable to allocate RAM_G space");
		s_ErrorGpuAllocFailed = 1;
	}
#endif

	return (Ft_Esd_GpuHandle) {
		.Id = MAX_NUM_ALLOCATIONS,
		.Seq = 0
	};
}

ft_uint32_t Ft_Esd_GpuAlloc_Get(Ft_Esd_GpuAlloc *ga, Ft_Esd_GpuHandle handle)
{
	if (handle.Id < MAX_NUM_ALLOCATIONS)
	{
		if (ga->AllocRefs[handle.Id].Seq == handle.Seq)
		{
			ft_uint16_t id = handle.Id;
			ft_uint16_t idx = ga->AllocRefs[id].Idx;
			ga->AllocEntries[idx].Flags |= GA_USED_FLAG;
			return ga->AllocEntries[idx].Address;
		}
	}

	return ~0;
}

void Ft_Esd_GpuAlloc_CollapseFree(Ft_Esd_GpuAlloc *ga, ft_uint32_t idxat)
{
	int shift = 0;
	if (idxat + 1 < ga->NbAllocEntries && ga->AllocEntries[idxat + 1].Id == MAX_NUM_ALLOCATIONS)
	{
		// Next entry is free, add to collapse
		++shift;
		ga->AllocEntries[idxat].Length += ga->AllocEntries[idxat + 1].Length;
	}
	if (idxat > 0 && ga->AllocEntries[idxat - 1].Id == MAX_NUM_ALLOCATIONS)
	{
		// Previous entry is free, add to collapse
		--idxat;
		++shift;
		ga->AllocEntries[idxat].Length += ga->AllocEntries[idxat + 1].Length;
	}
	if (shift)
	{
		// Collapse indices
		ga->NbAllocEntries -= shift;
		for (int idx = idxat + 1; idx < ga->NbAllocEntries; ++idx)
		{
			ga->AllocEntries[idx] = ga->AllocEntries[idx + shift];
			int id = ga->AllocEntries[idx].Id;
			if (id < MAX_NUM_ALLOCATIONS)
			{
				ga->AllocRefs[id].Idx = idx;
			}
		}
	}
}

void Ft_Esd_GpuAlloc_FreeId(Ft_Esd_GpuAlloc *ga, int id)
{
	// ESD_print("Free id %i\n", id);

#ifdef ESD_SIMULATION
	s_ErrorGpuAllocFailed = 0;
#endif

	int idx = ga->AllocRefs[id].Idx;

	// Invalidate handle reference
	ga->AllocRefs[id].Idx = MAX_NUM_ALLOCATIONS;
	++ga->AllocRefs[id].Seq;

	// Free entry
	ga->AllocEntries[idx].Id = MAX_NUM_ALLOCATIONS;
	ga->AllocEntries[idx].Flags = 0;

	// Collapse neighbouring entries
	Ft_Esd_GpuAlloc_CollapseFree(ga, idx);
}

void Ft_Esd_GpuAlloc_Free(Ft_Esd_GpuAlloc *ga, Ft_Esd_GpuHandle handle)
{
	int id = handle.Id;
	if (id < MAX_NUM_ALLOCATIONS
		&& ga->AllocRefs[id].Seq == handle.Seq)
	{
		Ft_Esd_GpuAlloc_FreeId(ga, id);
	}
}

void Ft_Esd_GpuAlloc_Update(Ft_Esd_GpuAlloc *ga)
{
	for (int idx = 0; idx < ga->NbAllocEntries; ++idx)
	{
		// Check if allocation entry is allocated
		if (ga->AllocEntries[idx].Id < MAX_NUM_ALLOCATIONS)
		{
			// If GC flag is set and used flag is not set, free this memory
			if (ga->AllocEntries[idx].Flags & GA_GC_FLAG)
			{
				if (!(ga->AllocEntries[idx].Flags & GA_USED_FLAG))
				{
					Ft_Esd_GpuAlloc_FreeId(ga, ga->AllocEntries[idx].Id);

					// Due to free collapse, the current idx may become another allocated entry
					--idx;
					continue;
				}
			}

			// Always clear the used flag on update
			ga->AllocEntries[idx].Flags &= ~GA_USED_FLAG;
		}
	}
}

// Get total used GPU RAM
ft_uint32_t Ft_Esd_GpuAlloc_GetTotalUsed(Ft_Esd_GpuAlloc *ga)
{
	ft_uint32_t total = 0;
	for (int idx = 0; idx < ga->NbAllocEntries; ++idx)
	{
		// Check if allocation entry is allocated
		if (ga->AllocEntries[idx].Id < MAX_NUM_ALLOCATIONS)
		{
			// Add the size of the allocated block to the total
			total += (ft_uint32_t)ga->AllocEntries[idx].Length;
		}
	}
	return total;
}

// Get total GPU RAM
ft_uint32_t Ft_Esd_GpuAlloc_GetTotal(Ft_Esd_GpuAlloc *ga)
{
	return RAM_G_SIZE;
}

#ifndef NDEBUG
void Ft_Esd_GpuAlloc_Print(Ft_Esd_GpuAlloc *ga)
{
	ESD_print("GpuAlloc:\n");
	for (int idx = 0; idx < ga->NbAllocEntries; ++idx)
	{
		ESD_print("%i: id: %i, addr: %i, len: %i, flags: %i\n",
			idx,
			(int)ga->AllocEntries[idx].Id,
			(int)ga->AllocEntries[idx].Address,
			(int)ga->AllocEntries[idx].Length,
			(int)ga->AllocEntries[idx].Flags);
	}
}
#endif

/* end of file */
