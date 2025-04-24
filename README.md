## Michigan Hackers EWI

# Intro
Thanks for visiting this project page!
I'm a Computer Engineering student here at the University of Michigan with a focus on Embedded + DSP. As such, projects like these are up my alley, especially with my involvement in music since youth!
I'm a Clarinet/Saxophone player as well as synthesizer/piano player. As such, this project was fun to build, as it incorporates two things I like

Michigan Hackers Embedded Systems Subteam was able to provide materials to build this project. If you're a student of UofM, please come check it out!

# Project Discussion
Here's an Electronic Wind Instrument in a box! I was able to build this in the span of a night, so the quality currently is very low.

The Teensy Audio Shield generates audio and outputs it through a mono audio amplifier to a single 5V speaker.

A simple air pressure sensor is used to track user breath input. Due to no CAD being done for the project, a simple straw sourced from a local Taco Bell was used. This led to some rather inconsistent pressure readings. As such, I included an additional ability to trigger note playing when sucking in, as a change in pressure in the negative direction is much more noticeable than the inconsistent pressure readings of blowing out.

A gyroscope is included in the build, but the code to integrate it was not completed. Ideally, this alters an audio effect of choice. I think it'd make more sense to implement it with more volume adjustment, as most wind players sway often, and volume changes as the bell of the horn moves around.

The two potentiometers alter Chorus and Reverb.

# Images
![20250423_232354](https://github.com/user-attachments/assets/4ce47fad-951a-4dd6-9e46-72eaa731986f)

![20250423_232441](https://github.com/user-attachments/assets/f5e032a2-74d8-45b5-906b-8221bfb69eba)

# Further Discussion
I will attempt to clean up the design much further, ideally through a CAD model. 

I'd like to stray away from using the 4x4 Keypad, as the model I used was inconsistent and seemed to have some faulty internal routing, as multiple buttons are unusable. I'd likely do this through some touchpads, or I might use a touch sensor strip and emulate something like a slide saxophone.

Overall, there are many improvements to make. Going to take the summer to fix things up and hopefully update!

