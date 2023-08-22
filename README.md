# CYNTHIA

Cross-platform AI library that consists of computer vision, image processing, machine learning, and deep learning tools
We will use CYNTHIA to recreate a simple version of the [terrain navigation system](https://science.nasa.gov/technology/technology-highlights/terrain-relative-navigation-landing-between-the-hazards)(TRN). Given our limitations as robotic, electric, and mechatronics engineers, we have developed a relatively simpler solution that could effectively act like the genuine TRN system used for space exploration. Our idea consists of using a balloon with cameras and sensors to autonomously navigate and land in unfamiliar terrain.

### Components
- Use a weather balloon or small tethered blimp as the aerial platform. Equip it with lightweight cameras, GPS, and sensors like ultrasonic altimeters.
- Stream aerial footage to a ground station laptop to process in real-time using CYNTHIA's computer vision and machine learning tools.
- Train a neural network model to identify safe landing zones from the aerial imagery as the balloon floats across the terrain.
- Use the GPS coordinates of identified landing zones to autonomously navigate the balloon platform to those locations.
- Employ computer vision techniques like optical flow and LIDAR simulation to estimate altitude and descent rate for landing.
- Activate a servo to release a light-weight landing mechanism like a cardboard model when approaching the landing coordinate.
- Refine CYNTHIA's algorithms over multiple iterations and types of terrain. Evaluate landing precision.
- Expand the project by using a programmable drone platform and integrating waypoint navigation.

### CYNTHIA's Features
* [&#x2713;] ~~Logging System~~ 
* [&#x2713;] ~~Event System~~
* [&#x2713;] ~~Platform Independent Window~~
* [ - ] User Graphics oct/7
* [ - ] Image Processing Algorithms sept/9
* [ - ] Recognition Algorithms sept/14
* [ - ] File Parsings (XML, YAML, JSON) sept/14
* [ - ] Cloud Integration sept/16
* [ - ] cynthia microprocessor Dec/21
* [ - ] Driver for Arducam to cynthia microprocessor jan/23
