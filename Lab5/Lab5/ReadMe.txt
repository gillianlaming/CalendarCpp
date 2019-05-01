Lab 5 Readme.

Group members: Gillian Laming, Natalie Stollman


NOTES:
1. Our implementation of the calendar uses military time. All times are assumed to be military time.
2. When adding an event to the calendar, you cannot include spaces in your input line.
3. I have cited a source in CalendarInterface.cpp. I copied the structure of a portion of my code from a C++ reference guide. Here is the link again: http://www.cplusplus.com/forum/general/102485/
4. When zooming into a specific day from the month view, the index for a day is the day of the month -1. For instance, if you want to view January 2, 2019, you would zoom into index 1.

ERRORS ENCOUNTERED OVER COURSE OF THE LAB:
1. non-standard syntax, use '&" to create a pointer to member. This happened when I didn't include () behind a method. eg vector a; a.size; --> a.size();
2. Error with recurring events starting on wrong date - fixed by fully packing the struct tm, so that the addDays function could convert from time_t to a stuct tm successfully.
3. We had an issue adding events if users were not on the calendar view (couldn't have zoomed in) - fixed by changing the DisplayableComponent we were passing through to the build methods.
4. Error with defining operator< again to sort tasks in todo. It would not build with two definitions and we couldn't override so I had to move the implementation for both into one. I check if I can dynamically cast the param into a DisplayableEvent vs a Task and based on that, do proper sorting.
5. When restoring a calendar from a file, we had to iterate over the multimap of events, but we couldnt delete events in the for loop because that wreaked havoc on our iterative process. Instead we pushed all the events onto a vector, and then went through the vector and deleted each event.

TEST CASES:

// answer the following questions
1. Part 2.1: Adding events to the calendar
Think about the separation of concerns in the project. 
What class/classes is responsible for the user interface of the Calendar?

Calendar Interface - deals mostly with user input, taking the input and directing the flow of events according to input.
It outputs the options available to the user and takes their input in.

What class/classes is responsible for managing the representation and construction of the Calendar?

CalendarBuilder and FullCalendarBuilder deal with the construction of the Calendar. The Calendar class is the object that is actually built from the FullCalendarBuilder. 

Which class should handle collecting information from the user about an event?
Calendarinterface.cpp - takes in information about an event from the user input and uses the info to call addEvent().

Which class should handle constructing and adding the event to the Calendar?
FullCalendarBuilder handles cosntructing/building the event, and calendar iterface handles adding the event to the calendar itself.

2. Part 2.2 Make the calendar interactive
How did you decide to efficiently search for an event by name?

We took in the name of the event to be searched for from the user, then used the multimap of events to search for the given name as a key. Therefore, it only iterates through existing events, not all days/dates, making it more efficient than iterating through all dates. Additionally, we decided to use the multimap STL container because it allowed you to have two+ entries with the same key. Since our calendar successfully supports event repetition, this is an important thing to have. If the user searches for an event by name that is mapped to more than one event object, then the user is given a list of events of which to choose from (to be displayed). 


Which object in the project understands the structure of the Calendar? Which object should be responsible for jumping to a specific object in the Calendar?

We use the builder to construct a displayable component of the granularity we want to display, and then the currentDisplay to actually display that component. In particular, we used the getComponentByDate method that we wrote in FullCalendarBuilder to get the component of interest.

How did you design saving/restoring the calendar to/from a file? What information needs to be saved about a Calendar to successfully restore it?

To Save, we used an ofstream and iterated through the multimap to save the events (events are all that needs to be saved) to a file and wrote them to the file with the same formatting we display them with. 
To Restore, we ise an ifstream to open the file and iterate through it with an isstream, parsing each line, creating an event based on the info from each line, and adding the event to the calendar. The only information that needed to be saved in order for calendars to be saved and restored was event information. We stored the name of the calendar in the file name.

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
to implement this change. Many of the others remained similar, with perhaps minor changes. Addtionally, since most of the functions we changed were overloaded, it made it particularily easy to change function parameters.



How does your implementation maintain flexibility and extensibility of the project? Compare this with other designs you considered.

Our implememntation's use of shared pointers allows for us to access children and parents and could be easily extended because of this. Additionally, we did not hardcode. Instead, we used variables and typedefs that were declared in header files to represent constants. This makes our project adaptable to different types. We saw firsthand how adaptable and extensible our project is when we implemented the ToDOList and the new calendar builder (IncrementalCalendarBuilder).
We also considered other implementations before realizing hoe useful shared pointers would be here, and our current implementation proved to maintain flexibility and extensibility.



Part 3 (only answer the questions pertaining to the functionality you chose to implement)
3.1: Merging calendars
Describe the benefits of the Decorator pattern? If you used the decorator pattern, how was it applied to 
support merging calendars?

The decorator pattern is helpful because it allowed us to add additional fucntionality to an object in our class without having to revamp the rest of our code. For the merging, we had to add a calendar that was associated with each event after the merge, but leave the orginal events in the calendar unchanged. this is where the decorating came in -- we "decorated" the events that were from the merge (with the name of the calendar they came from), and left the orginail events of the base calendar unchanged as is. The output of the events showed the calendar associated with each event (if the event had come from a merged calendar) which indicated that we were correctly using the Decorator Pattern.


If you chose not to use the decorator pattern, how does your design compare with it when 
considering flexibility and extensibility of the design? 
n/a, we used the decorator pattern.




3.2 ToDo List
Describe your implementation? How does it support easy extensibility of the project in the future?
How is the singleton pattern used to enforce only a sigle TODO list instance?

For our ToDo List, we created an entirely separate interface. Essentially, a Task is a displayable component and is a child of a todo list (a calendar componenet). 
In our calendar interface, if the user switches to ToDo view, a ToDoListInterface is created and they are brought to their options of addidng or completing tasks. 
It uses the same operator< as events do for sorting (see error explanantion) and the singleton pattern ensures that there is only one todo list at a time because
the build todo function will only build if one does not already exist. 



3.3 Incremental Builder
What challenges did you run into while implementing this? Were any changes to the builder interface required? 
How does using the builder pattern contribute to easily being able to change how an object(calendar in this case)
is represented?

This was definitely the hardest of the three implementations because of the changes we had to make to the foundation code for building a calendar. We decided to make a new builder called "IncrementalCalendarBuilder" which attempted to implement this part. We had to change the way buildDay, buildMonth, buildYear and getCOmponentByDate worked, and had to change the constructor. Something particularily challenging about this part was trying to figure out what components were null and what had to be built and when. The builder pattern made changing how an object is represented because it allowed for flexibility in constructing the calendar. This is what allowed to create two separate implementations of building the calendar.

**EXTRA CREDIT NOTE** The ToDoList and Merge were completed fully as components of this project. We implemented the IncrementalBuilder for extra credit. It is not fully implemented, however all of the structure and most of the code works for the Incremental Builder.
