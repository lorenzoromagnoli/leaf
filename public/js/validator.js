$(document).ready(function() {



	var jqxhr = $.getJSON("messages", function(data) {
			console.log("success");
		})
		.done(function(data) {
			console.log("second success");
			console.log(data);

			$.each(data, function(i, item) {

				if (item.approved=="true") {
					//items.push( "<li id='" + i + "'>" + item.message + "</li>" );
					$('#messages-validator').append('<tr class="valid" id="' + item._id + '">  <td class="message">' + item.message + '</td><td class="buttons"> <a class="action-ban">ban</a> <a class="action-delete">delete</a></td>  </tr>');
				} else {
					$('#messages-validator').append('<tr class="pending" id="' + item._id + '"><td class="message">' + item.message + '</td><td class="buttons"> <a class="action-approve">approve</a> <a class="action-delete">delete</a> </td> </tr>');
				}
			});

			handleButtons();

		})
		.fail(function() {
			console.log("error");
		})
		.always(function() {
			console.log("complete");
		});
});


function handleButtons(){
	$('.action-ban').click(function() {
		var msg_id=$(this).parent().parent().attr('id');
		editMessageStatus(msg_id,false)
	})
	$('.action-approve').click(function() {
		var msg_id=$(this).parent().parent().attr('id');
		editMessageStatus(msg_id,true)
	})

	$('.action-delete').click(function() {
		var msg_id=$(this).parent().parent().attr('id');
		deleteMessage(msg_id);
	})
}
