# VimBell
## An alarm clock app with Vim-like controls.

![vimbell_demo](https://media.giphy.com/media/w3GTYDTXvJkDIyJJBk/giphy.gif)

## How it works
- The program opens with the Rack Select screen.  
- This is where you can create a new rack or load an existing one.  
- A rack is just a list of alarms.  
- Unlike most alarm clock apps where there is just a single rack, here you can store seperate racks for different schedules you might have.  
- Each rack can hold 10 alarms, and each alarm can hold 10 follow-ups.  
- When creating a new rack, a text prompt will appear asking you to name the rack. (Note: the name must not contain any spaces between words).  
- After you've created or loaded a rack, the program will switch to the Rack View screen.  
- Here, you can add new alarms and edit existing ones, all by using just the keyboard.  
- There are 3 main interactive sections in the Rack Screen; the ***clock***, the ***message box***, and the ***rack***.  
- You can maneuver between each section using the HJKL keys, just like in Vim.  

## Controls
> ### Global
>> ***Escape*** : Exit  
>> ***Alt + Space*** : Silence all triggered alarms  
>
> ### Clock
>> ***Tab*** : Switch to the rack  
>> ***H*** : Move the selector left  
>> ***L*** : Move the selector right  
>> ***K*** : Increase the selected value by 1  
>> ***J*** : Decrease the selected value by 1  
>> ***Shift + K*** : Increase the selected value by 5  
>> ***Shift + J*** : Decrease the selected value by 5  
>> ***M*** : Toggle the meridiem (AM/PM)  
>> ***Enter*** : Submit this alarm/edit to the rack  
>
> ### Message Box
>> ***Tab*** : Switch to the rack  
>> #### Normal mode
>>> ***I*** : Switch to 'Insert' mode  
>>> ***H*** : Move the cursor left  
>>> ***L*** : Move the cursor right  
>>> ***Shift + H*** : Jump to front of the line  
>>> ***Shift + L*** : Jump to the end of the line  
>> ***Enter*** : Submit this alarm/edit to the rack  
>> #### Insert mode
>>> ***Escape*** : Switch to 'Normal' mode  
>>> ***Any character*** : Write that character to the field  
>>> ***Backspace*** : Delete the character behind the cursor  
>>> ***Shift + Backspace*** : Delete all characters behind the cursor  
>
> ### Rack
>> ***Tab*** : Switch to the message box  
>> ***K*** : Move the selector up  
>> ***J*** : Move the selector down  
>> ***Shift + K*** : Jump to the top of the rack  
>> ***Shift + J*** : Jump to the bottom of the rack  
>> ***E*** : Edit the selected alarm's message  
>> ***T*** : Toggle the active state of the selected alarm  
>> ***Enter*** : Add a new follow-up to the selected alarm  
>> ***Shift + Enter*** : Increase the follow-up interval time for the selected alarm by 5  
>> ***Backspace*** : Remove the latest follow-up from the selected alarm  
>> ***Shift + Backspace*** : Decrease the follow-up interval time for the selected alarm by 5  
>
> ### Pop-ups
>> ***Y or Enter*** : Yes  
>> ***N or Escape*** : No  
