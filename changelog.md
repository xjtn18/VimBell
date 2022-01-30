# VimBell Change Log


### 5/3/21
	- Fixed seg fault after adding an alarm by making the current rack a global variable. Member variables are in class scope and were not accessible by the clock thread.
	- Made sure to explicitly call delete on the global Rack to properly delete any audio devices open in the alarms. Globals do not fall out of scope and so are never being destructed, automatically atleast.
	- Changed name of 'MainApp/App' to 'Program'.

### 5/4/21
	- Changed currentRack to be a static member of the Rack class. Makes more sense here. Static vars still need to be explicity deleted.
	- Added a custom wxPanel class to process user key input. It is stored as a member the Frame.

### 5/7/21
	- Switched GUI framework to SFML. wxWidgets was hurting my soul.

### 5/9/21
	- Added up and down interface movement using J and K key input.

### 5/10/21
	- Added an update function in menu, and store relevant drawing information as members instead of using them only in the Menu constructor.
	- Can now duplicate list elements by activating them. Creates new element directly below and shifts the selector to the new element.

### 5/16/21
	- UI now updates whenever it detects user input; clears all buttons, recreates them based on current state of the alarm rack.
	- Made all alarm sounds route through one sound object; alarms will not trigger sound if an alarm is currently playing.
	- User can silence current alarm by pressing space.
	- User can toggle activeness of an alarm.
	- Fixed bug with alarms not copying over when pushing them into vectors/arrays by implementing copy constructors.
	- Fixed uninitialized 'stopped' bool in ThreadClock that was causing the clock to not run on some program starts.
	- Added various sounds to certain user actions.
	- Changed string representation of Time objects to a 12 hour clock.
	- Changed event loop to switch statement instead of if-else.
	- Can now use Backspace to delete an alarm from the rack.

### 5/19/21
	- Successfully displaying blinking type cursor.
	- Added black-magic TimerKiller class that can end a 'sleeping' task (destroys the cursor immediately, no wait)

### 5/23/21
	- Changed cursor blink implemenation to use delta-time and a lerp counter (standard practice, much cleaner and safer than using thread sleeps)
	- Removed 'Program' class which was nothing but a glorified namespace.
	- Added 2 main program modes TEXT and ALARM that correlate to seperate keybindings.
	- User can now type text into the main text field, pressing Enter then moves inserts an alarm into the rack with the text field contents as the alarm message + switches mode to 'ALARM'.
	- General refactoring.
	- Restructured how sounds are loaded and played. Sounds are loaded at program start into a hashmap and are played by a Speaker (previously called Sound) using '.play("sound_name.wav")'.

### 5/25/21
	- Added a 'duplicate increment' variable in Rack tha determines the time distance between dups.
	- Added barebones logical interface for increasing/decreasing the duplicate time distance IRT.
	- Alarms can no longer be 'duplicated' (created) in an empty rack; user should first write a message and commit it to the rack.
	- Added auto transitions between alarm and text mode (ex. when all alarms are deleted).
	- Rack menu now unhighlights the currently selected alarm when disengaging.
	- Changed text spacing in alarms to be left justified rather than centered, for readabilty.

### 5/30/21
	- Changed the color scheme to a darker style.
	- Added basic save and load functionality (see below)
	- Incorporated CAJUN: an opensoure JSON library. Program now saves the state of the current rack on exit to a JSON file called "R1.rack" for the time being. That file is then read on program start and the rack is recreated identically.
	- Added boolean to prevent 'text' and 'alarm' mode handling from processing events that occured in the global input handler.

### 5/31/21
	- Can now edit an alarms message by pressing 'e' in alarm mode.

### 6/5/21
	- Made character aligning with text fields much more intuitive and adaptive.
	- Added a placeholder digital clock interface to the left of the main text field.
	- Some UI design changes.
	- Wrote square-sine function that adjusts alpha of the cursor, rather than having a discrete blink.

### 6/8/21
	- Added ask_yes_no function to temporarily ask if user wants to save current rack on exit.
	
### 6/15/21:
	- cursor movement and text insertion for text fields.
	- Color inversion for characters underneath the cursor; matches the blink animation.

### 7/5/21:
	- made quit dialog interaction through UI rather than terminal.
	- refresh optimization of alarm rack display.
	- general refactor

### 7/11/21:
	- event handled through currently engaged entities.
	- universal events handled after entity events so keystroke overrides are easier to manage.
	- switched to liberation mono font.

### 7/12/21:
	- fixed program crashing bug: wasn't returning true in the 'edit' path of the rack event handled.

### 7/15/21:
	- Using COMMAND+LSHIFT (placeholder), user can engage the digital time view and edit the time.
	- Time set here will become the target of any newly created alarms.
	- Pressing 'm' will change the meridean.
	- Added a font loading macro to make loading new fonts less of a pain.
	- shifted the on some origins of characters in the libmono font.

### 7/17/21:
	- added selection arrows to indicate whether the hour is being modified or the minute is.
	- alarm rack insertions are now sorted based on target time. Added operator 'less' for jb::Time.
	- Switched some controls around.

### 1/10/22:
	- fixed out-of-bounds array indexing in Line when disengaging text fields; was causing random seg faults.
	- added AM/PM visualization and incroprated the Animation struct.
	- Messages added to alarms are now trimmed of all outer whitespace.

### 1/15/22:
	- added methods in Program that setup each pane; added a different pane at program start that lets users load/create a rack.
	- closing a rack brings user back to rack selection.
	- trimmed popup messages and limited alarms to 10 per rack to as to all fit on screen.
	- changed the controls for moving between rack, textbox, and time. Tab cycles clockwise, shift-tab cycles counter-clockwise.
	- triggered alarms are now highlighted red in the rack. Deleting/silencing/deactivating all triggered alarms ends the alarm tone.


