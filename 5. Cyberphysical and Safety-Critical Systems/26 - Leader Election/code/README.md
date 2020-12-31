# Code Readme
In index.js, I used the server-side database design pattern from the socket.io example given to us in the example folder and design patterns web link. In this program, I am able to read the textfile smoke.txt and gather that data to be placed in a database. Using collection.insert, I am able to insert specific data, such as the time, ID, smoke, and temperature into the database. In the code I have commented out an erase data function (collection.drop) that I use to reset the database before each run. Moreover, the query defined in this program allows the user to see all of the items inserted into the database, however, the user can be more specific and change the query to look for a specific ID or time to display on the console.

The other files provided show the smoke_data database, smoke.txt file provided, and other configuration items.

Sources
- [tingodb](http://www.tingodb.com/)
- [Design patterns](http://whizzer.bu.edu/briefs/design-patterns/dp-db)
- [Node socket.io example](https://github.com/BU-EC444/code-examples/tree/master/node-socketio)
- [Help on creating a javascript array](https://stackoverflow.com/questions/34857458/reading-local-text-file-into-a-javascript-array)
- [Query into Database help](https://www.w3schools.com/nodejs/nodejs_mongodb_query.asp)
