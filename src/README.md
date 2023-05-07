# MQTT general notes
* as little states as possible, but reactors sending details for each light
	* a python reactor for every piece of hardware -> derived classes depending on hardware (outlet, tasmota, my own stuff)
* what logic should run on the ESP?
	* do not distinguish between different lights/rooms/whatever
		* do not subscribe to bedroom/color but instead have a reactor subscribe to bedroom/color and update all lights accordingly
	* programs can run and receive input fine


# ESP Firmware Requirements

* MQTT Client ID based on Mac Address
	* Name received as retained message on state/mac/[address]/name (or so)
	* Setup and subscribe topics based on Name (or topics at state/mac/[address]/#)

* MQTT broker needs fixed hostname (dns? no idea)
* Messages have to be received at all times -> slim callback and loop functions
* ZylProg-like behaviour
	* zylProg.render() every loop
	* received message gets passed as zylProg.input() and stuff like fade and transitions are calculated each render() step
	*-> opportunity to actually add zylProgs

### setup() and loop() outlines:
setup()
* connect to wifi
* init MQTT client
* subscribe to mac-address-topic
	* while(true) mqttclient.loop() until name is received
	* temporary callback (lambda?) -> our only job is to receive our name right now
	* do stuff depending on who we are
* init all other stuff necessary (e.g. ArduinoOTA with hostname, or zylProgs)
* set our proper mqttclient callback function
* subscribe to all topics important for us
	* prepare for a flood of retained messages? (-> have this be the last step?)

loop()
* mqttclient.loop()
* program.render()
* ota.handle()

# MQTT topic tree
all topics start with reactor/[name]/...

### Monochrome RGB strip
/program
* default
* rainbow
* fire
* whatever

/color
* primary color

/color/[number]
* add as many colors as desirable for modes?
* /color/1 has to be the same as /color -> backend
* retained messages can be cleared by sending "" 
	* which order do retained messages get sent when we subscribe to [name]/#?
	* how to avoid colors 1, 2, 4 being set and 3 being unset? which ones to use? -> backend? reactors?

/brightness

### RGBW strip or White/Warmwhite (?)
/lighttemperature
* not sure about this, maybe communicate light temperature in /color instead?

### ARGB strip
shouldnt be too different from monochrome, from a MQTT API standpoint
