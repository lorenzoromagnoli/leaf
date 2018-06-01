
function showIntro(){
	$('#intro').toggleClass("hidden", false);
	$('#form').toggleClass("hidden", true);
	$('#thankyou').toggleClass("hidden", true);
}


function showForm(){
	$('#intro').toggleClass("hidden", true);
	$('#form').toggleClass("hidden", false);
	$('#thankyou').toggleClass("hidden", true);
}

function showThankYou(){
	$('#intro').toggleClass("hidden", true);
	$('#form').toggleClass("hidden", true);
	$('#thankyou').toggleClass("hidden", false);
}
