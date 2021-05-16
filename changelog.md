# jBell Change Log


### 5/3/21
	- Fixed seg fault after adding an alarm by making the current rack a global variable. Member variables are in class scope and were not accessible by the clock thread.
	- Made sure to explicitly call delete on the global Rack to properly delete and audio devices open in the alarms. Globals do not fall out of scope and so are never being destructed, automatically atleast.
	- Changed name of 'MainApp/App' to 'Program'.

### 5/4/21
	- Changed currentRack to be a static member of the Rack class. Makes more sense here. Static vars still need to be explicity deleted.
	- Added a custom wxPanel class to process user key input. It is stored as a member the Frame.

### 5/7/21
	- Switched GUI framework to SFML. wxWidgets was hurting my soul.

### 5/9/21
	- Added up and down interface movement using J and K key input.

### 5/10/21
	- Added an update function in menu, and store relevant drawing information as memebers instead of using them only in the Menu constructor.
	- Can now duplicate list elements by activating them. Creates new element directly below and shifts the selector to the new element.

### 5/16/21
	- UI now updates whenever it detects user input; clears all buttons, recreates them based on current state of the alarm rack.
	- Made all alarm sounds route through one sound object; alarms will not trigger sound if an alarm is currently playing.
	- User can silence current alarm by pressing space.
	- Use can toggle activeness.
	- Fixed bug with alarms not copying over when pushing them into vectors/arrays by implementing copy constructors.
	- Fixed uninitialized 'stopped' bool in ThreadClock that was causing the clock to not run on some program starts.
	- Added various sounds to certain user actions.


### TODO:



### Syntax Formatting
	- Class names: 				"ClassName"
	- Function names: 			"function_name"
	- SFML function names:		"functionName"
	- Variable/Object names:	"object_name"
	- Globals:						"GLOBAL"


## Structure:
	- Make all user input interact directly with the state (model) of the program. Then have the UI update every frame based on the current state of that model.  (?)
	- To avoid circular dependency issues between parent and child relationships that use each other, forward declare the class in the header file and then include the classes header in the SOURCE file. (probably bad design if needed)
	- Store "global" objects as static members of the class that is its type. (must be pointers)
	- When creating global device objects (like sf::Sounds), store them as unique/shared pointers on heap so they can be explicity deleted (reset()) at program end. This removes any error messages about devices not being closed when we exit.


