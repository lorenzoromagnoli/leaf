const express = require('express')
const bodyParser = require('body-parser')
const app = express()
var db;
var ObjectId = require('mongodb').ObjectID;
var path = require("path");

app.use(express.static('public'))
app.use(bodyParser());

var dbstarted=false;

var mqtt = require('mqtt');

var mqttclient = mqtt.connect('mqtt://broker.shiftr.io', {
	clientId: 'leaf_Server',
	username: 'ebd3575a',
	password: '39bccc93d8b275b1'
});

mqttclient.on('connect', function() {
	console.log('mqtt client has connected!');

	// mqttclient.subscribe('/example');
	// //mqttclient.unsubscribe('/example');
	//
	// setInterval(function(){
	//   mqttclient.publish('/hello', 'world');
	// }, 1000);
});
//
// mqttclient.on('message', function(topic, message) {
//   console.log('new message:', topic, message.toString());
// });
//connect to the db when the app starts
const MongoClient = require('mongodb').MongoClient
MongoClient.connect('mongodb://leaf:leaf_holden@ds263089.mlab.com:63089/leaf', (err, client) => {
	if (err) return console.log(err)
	db = client.db('leaf') // whatever your database name is
	dbstarted=true;
	// ... start the server
	app.listen(3000, () => console.log('leaf backend is listening on port 3000!'))
})


//here I set a timer that dispatch the messages to the Arduinos
var n_screenXArduino = 8;
var n_arduinosControllingScreend = 5;







//the root basically is useless
app.get('/', (req, res) => {
	res.sendFile(path.join(__dirname + '/public/index.html'));
});

//when you send something from the form it saves it in the db
app.post('/newMessage', (req, res) => {
	console.log(req.body);
	db.collection('memories').save(req.body, (err, result) => {
		if (err) return console.log(err)
		console.log('saved to database')
		res.send('saved to database');
		mqttclient.publish('/glow', 'now');
		mqttclient.publish('/printer', req.body.message);

	})
})

app.post('/updateMessage', (req, res) => {
	console.log(req.body);

	var myquery = {
		_id: ObjectId(req.body.id)
	};
	var newvalues = {
		$set: {
			approved: req.body.approved
		}
	};
	db.collection('memories').update(myquery, newvalues, (err, result) => {
		if (err) return console.log(err)
		res.send('modified db');
	})
})


//when you send something from the form it saves it in the db
app.post('/deleteMessage', (req, res) => {
	console.log("deleting message:" + req.body);
	db.collection('memories').deleteOne({
		"_id": ObjectId(req.body.id)
	}, (err, result) => {
		if (err) return console.log(err)
		res.send('deleted');
	});

})


//returns all the messages in the db as json
app.get('/messages', (req, res) => {
	var cursor = db.collection('memories').find().toArray(function(err, results) {
		//console.log(results)
		// send HTML file populated with quotes here
		res.send(JSON.stringify(results));
	})
})

app.get('/getRandomMsg', (req, res) => {
	var query = {
		approved: 'true'
	};

	db.collection('memories').count(query, function(err, count) {
		console.log(count);
		var r = Math.floor(Math.random() * count);
		console.log(r);

		var randomElement = db.collection('memories').find(query).limit(1).skip(r, ).toArray(function(err, results) {
			console.log(results);
			res.send(results);
		});
	});
})



setInterval(function() {

	if (mqttclient.connected && dbstarted) {

		var query = {
			approved: 'true'
		};
		db.collection('memories').count(query, (err, count) => {

			if (err) return console.log(err)
			if (count > 0) {

				random_Arduino = Math.floor(Math.random() * n_arduinosControllingScreend);
				random_Screen = Math.floor(Math.random() * n_screenXArduino);
				console.log("changing screen n." + random_Screen + " of Arduino n." + random_Arduino);

				var r = Math.floor(Math.random() * count);
				//console.log("" r);

				var randomElement = db.collection('memories').find(query).limit(1).skip(r, ).toArray((err, results) => {
					if (err) return console.log(err);

					console.log("new sentence is " + results[0].message);
					var index = random_Screen + 1
					mqttclient.publish('/arduino' + random_Arduino + '/screen' + index, results[0].message);
				});
			}

		});
	}

}, 1000);
