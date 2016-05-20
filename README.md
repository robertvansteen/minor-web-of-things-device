# IoT device

## Idea
The idea was to create a blueprint of a C++ application that can be used on many
devices in a way that they can communicate in an easy, structured way with my
[IoT network](https://github.com/reauv/minor-web-of-things-sensors-server).

## How does it work
Before I started this project I never worked with C++ before so it was quite
the learning experience for me, having almost no prior experience with types,
references and pointers. The codebase became (at least for me) pretty complex but
now that it's finished I'm quite satisfied with it.

The idea behind the codebase is that it wraps a big abstraction around sending &
receiving the messages via MQTT. For example, it automatically prepends the
device ID to the message when you send one. The 2 most import files to modify are
the `inputManager` and `outputManager`. For every input or outputdevice connected
you can create a custom class and load these in the maanger. After that they
get automatically registered.

### InputDevices
Input devices have a `loop` method that is called every loop of the program. This
gives you the opportunity to do whatever you want, for example reading a sensor.
There is a `publish` method on the input class that you can use that doesn't
even require you to specify a topic, just pass in a JSON object and you're good to go!

### OutputDevices
Output devices work a little bit different and instead of a loop method, they
have a `callback` method that gets called when a topic corresponding with the
output device gets called from outside. You get the data passed along so you can
do whatever you want to do with it!
