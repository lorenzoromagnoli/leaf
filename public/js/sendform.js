
$( document ).ready(function() {
    console.log( "ready!" );
		$("#sendform-button").on('click', function () {
			var message=document.getElementById("message").value;
			console.log (message);
			saveNewMessage(message)
		});
});

function saveNewMessage(message){
	var messageToSend={
		'message':message,
		'approved':false
	};

	$.post('/newMessage', messageToSend, function(data){
		$( ".result" ).html( data );
	});
}

function editMessageStatus(message_id,approved){
	var messageToSend={
		'id':message_id,
		'approved':approved
	};

	console.log(messageToSend);

	$.post('/updateMessage', messageToSend, function(data){
	});
}
