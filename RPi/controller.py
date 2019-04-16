from Detection.MotionDetector import MotionDetector
import yaml
from Utilities.CoordinatesGenerator import CoordinatesGenerator
from Utilities.colors import COLOR_RED
import cv2
import os
import threading
import queue


class Controller:

    REFERENCE_FILE = 'reference.png'
    SERIAL_PORT    = '/dev/ttyAMA0'




    def __init__(self, **kwargs):
        self.data_file   = kwargs.get('data_file')
        self.stream_url  = kwargs.get('stream_url')
        self.video_path  = kwargs.get('video_path')
        self.baudrate    = kwargs.get('baudrate')

        if not os.path.exists(self.data_file) or os.path.getsize(self.data_file) == 0:
            self._init_boxes()

        self.coordinates   = self._init_coordinates()
        self.detector      = self._init_detector()
        self.serial_port   = self._init_port()
        self.serial_buffer = queue.Queue()
        self.serial_thread = threading.Thread(target=self.read_serial,
                            args=serial_buffer, daemon=True)




    def _init_coordinates(self):
        with open(self.data_file, 'r') as FILE:
            data = yaml.load(FILE)
        return data


    def _init_detector(self):
        """Initializes the motion detector.
        """
        return MotionDetector(self.coordinates)

    def _init_port(self):
        """Initializes the serial port.
        """
        return serial.Serial(Controller.SERIAL_PORT,
                             self.baudrate)


    def _init_boxes(self):
        """Initializes bounding boxes for parking spots.
        """
        # Capture a reference image
        if self.video_path:
            cap = cv2.VideoCapture(self.video_path)
        elif self.stream_url:
            cap = cv2.VideoCapture(self.stream_url)
        else:
            raise ValueError('Need URL or Path.')

        _, frame = cap.read()
        # Save the image
        cv2.imwrite(Controller.REFERENCE_FILE, frame)

        cap.release()
        # Generate coordinates
        with open(self.data_file, "w+") as FILE:
            generator = CoordinatesGenerator(Controller.REFERENCE_FILE, FILE, COLOR_RED)
            generator.generate()



    def read_serial(self, queue):
        logging.info('Reading serial data')
        while(True):
            received_line = self.readline()
            queue.put(received_line.decode())
            logging.info('Received {}'.format(received_line.decode()))


    def run(self):
        # Start the Serial IO thread
        # Fetch the video capture

        # Get a frame
        # Detect vacant spots
        #

        if self.video_path:
            cap = cv2.VideoCapture(self.video_path)
        elif self.stream_url:
            cap = cv2.VideoCapture(self.stream_url)



        while(cap.isOpened()):
            _, frame  = cap.read()

            new_frame, statuses = self.detector.detect_motion(frame)

            cv2.imshow('Video', new_frame)

            # logging.info('Updating Server...')
            self._update_web_server()
            # logging.info('Updating MCU...')
            self._update_mcu()

            if cv2.waitKey(1) & 0xFF == ord("q"):
                break

        cap.release()
        cv2.destroyAllWindows()


    def _update_web_server(self):
        pass

    def _update_mcu(self):
        pass



