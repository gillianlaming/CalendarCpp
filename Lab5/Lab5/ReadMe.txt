Lab 5 Readme.

Group members: Gillian Laming, Natalie Stollman


NOTES:
1. Our implementation of the calendar uses military time. All times are assumed to be military time.
2. when adding an event to the calendar, you cannot include spaces in your input line.
3. I have cited a source in CalendarInterface.cpp. I copied the structure of a portion of my code from a C++ reference guide. Here is the link again: http://www.cplusplus.com/forum/general/102485/
4. when zooming into a specific day from the month view, the index for a day is the day of the month -1

ERRORS ENCOUNTERED OVER COURSE OF THE LAB:
1. non-standard syntax, use '&" to create a pointer to member. this happened when i didn't include () behind a method. eg vector a; a.size; --> a.size();
2. Error with recurring events starting on wrong date - fixed by fully packing the struct tm
3. we had an issue adding events if users were not on the calendar view (couldn't have zoomed in) - 



// answer the following questions
1. Part 2.1: Adding events to the calendar
Think about the separation of concerns in the project. 
What class/classes is responsible for the user interface of the Calendar?

Calendar Interface - deals mostly with user input, taking the input and directing the flow of events according to input.
It outputs the options available to the user and takes their input in.

What class/classes is responsible for managing the representation and construction of the Calendar?

calendarBuilder and FullCalendarBuilder deal with the construction of the Calendar. Calendar interface helps with the representation.

Which class should handle collecting information from the user about an event?
calendarinterface.cpp - takes in information about an event from the user input and uses the info to call addEvent()

Which class should handle constructing and adding the event to the Calendar?
calendar builder handles cosntructing/building the event, and calendar itnerface handles adding the event to the calendar itself.

//notes
- displayable component is responsible for displaying days/months/years and cal itself


2. Part 2.2 Make the calendar interactive
How did you decide to efficiently search for an event by name?
We took in the name of the event to be searched for from the user, then used the multimap of events to search through
for the given name as a key. Therefore, it only iterates through existing events, not all days/dates.

//TODO: gillian you did this part can u answer it

Which object in the project understands the structure of the Calendar? Which object should be responsible for jumping to a specific object in the Calendar?



How did you design saving/restoring the calendar to/from a file? What information needs to be saved about a Calendar to successfully restore it?

To Save, we used an ofstream and iterated through the multimap to save the events (events are all that needs to be saved)
to a file and wrote them to the file with the same formatting we display them with. 
To Restore, we ise an ifstream to open the file and iterate through it with an isstream,  taking in each event and calling 
an addevent helper function to add these events to the calendar. 




3. Part 2.3 Updating the display
How a particular component in the calendar should be displayed depends on what the current display of the calendar is.
How did you implement this functionality? 

We created an integer variable called depth, which we made a parameter of all display() functions. 
Essentially, the full calendar view is a depth of 4, year is 3, month is 2, day is 1, and event is 0.
Depending on the depth, each display function behaves accordingly by using if statements to check
current depth and couting the correct/relavent information in the proper format.






Did you make any changes to the interfaces provided in the starter code? If so, how easy was it to 
refactor the code to match this change? 

We changed the display functions quite a bit. We even added a parameter to this function, but it was not especially hard
to implement this change. Many of the others remained similar, with perhaps minor changes.



How does your implementation maintain flexibility and extensibility of the project? Compare this with other designs you considered.







Part 3 (only answer the questions pertaining to the functionality you chose to implement)
3.1: Merging calendars
Describe the benefits of the Decorator pattern? If you used the decorator pattern, how was it applied to 
support merging calendars?






If you chose not to use the decorator pattern, how does your design compare with it when 
considering flexibility and extensibility of the design? 







3.2 ToDo List
Describe your implementation? How does it support easy extensibility of the project in the future?
How is the singleton pattern used to enforce only a sigle TODO list instance?








3.3 Incremental Builder
What challenges did you run into while implementing this? Were any changes to the builder interface required? 
How does using the builder pattern contribute to easily being able to change how an object(calendar in this case)
is represented?
