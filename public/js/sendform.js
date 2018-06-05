
$( document ).ready(function() {
    console.log( "ready!" );
		$("#sendform-button").on('click', function () {
			var message=document.getElementById("message").value;
			console.log (message);
			console.log (message.normalize('NFD').replace(/[\u0300-\u036f]/g, ""));

			saveNewMessage(message.normalize('NFD').replace(/[\u0300-\u036f]/g, ""))
		});
});


//str.normalize('NFD').replace(/[\u0300-\u036f]/g, "")


function saveNewMessage(message){
	var messageToSend={
		'message':message,
		'approved':false
	};

	$.post('/newMessage', messageToSend, function(data){
		$( ".result" ).html( data );
		showThankYou();

		setTimeout(showIntro, 10000);

	});
}

function editMessageStatus(message_id,approved){
	var messageToSend={
		'id':message_id,
		'approved':approved
	};

	console.log(messageToSend);

	$.post('/updateMessage', messageToSend, function(data){
		console.log("done");
		location.reload();

	});
}

function deleteMessage(message_id){
	var messageToSend={
		'id':message_id,
	};

	$.post('/deleteMessage', messageToSend, function(data){
		console.log("done deleting");
		location.reload();
	});
}
