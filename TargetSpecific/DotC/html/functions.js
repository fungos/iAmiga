function landScapeAction() {
	$('#landscapeOverlay').addClass("fadein");
}

function loadslidedown(page) {
	document.getElementById('spinner').style.display='block';
	$.get(page, function(data) {
  		$('#slidedownmenupage').html(data);
	
		menu.open();
		$('#spinner').fadeOut('fast', function() { });
	});
}

var number = 0;

function loadpage(to, transition, externalpath) {
	
if(to!=from) {
	if (transition == undefined)
	transition = 'NONE';
		
	var trNone = transition == 'NONE';
	var trFade = transition == 'FADE';
	var trFlipRight = transition == 'FLIP_LEFT';
	var trFlipLeft = transition == 'FLIP_RIGHT';
	var trSlideUp = transition == 'SLIDE_UP';
	var trSlideUpBack = transition == 'SLIDE_UP_BACK';
	var trSlideDown = transition == 'SLIDE_DOWN';
	var trSlideDownBack = transition == 'SLIDE_DOWN_BACK';
	var trSlideRight = transition == 'SLIDE_RIGHT';
	var trSlideLeft = transition == 'SLIDE_LEFT' || transition == 'DEFAULT';
	
	if ($('#'+to).length == 0) {
		document.getElementById('spinner').style.display='block';	
		if(externalpath) {
			$.get(externalpath+to+'.html', function(data) {
	  			$('#left').append(data);
					doTransition();
					$('#spinner').fadeOut('slow');
				});	
		} else {	
		$.get(to+'.html', function(data) {
  			$('#left').append(data);
				doTransition();
				$('#spinner').fadeOut('slow');
			});
		}
		} else {
			doTransition();
		}

		function doTransition() {
			$('#'+from).attr("class", "");
			$('#'+to).attr("class", "");
	
			if(trSlideLeft)
			{
				$('#'+from).attr("active", "false").addClass("transthis slide out");
        		$('#'+to).attr("active", "true").show().addClass("transthis slide in");
				number = number+1;
				backtransition = "SLIDE_RIGHT";
			} else if(trSlideRight) {
				$('#'+from).attr("active", "false").addClass("transthis slide out reverse");
        		$('#'+to).attr("active", "true").show().addClass("transthis slide in reverse");
			} else if(trSlideUp) {
				$('#'+from).attr("active", "false").addClass("transthis slideup out");
       			$('#'+to).attr("active", "true").show().addClass("transthis slideup in");
				number = number+1;
			} else if(trSlideDown) {
				$('#'+from).attr("active", "false").addClass("transthis slidedown out");
       			$('#'+to).attr("active", "true").show().addClass("transthis slidedown in");
				number = number+1;
			} else if(trSlideDownBack) {
				$('#'+from).attr("active", "false").addClass("transthis slidedown out reverse");
       			$('#'+to).attr("active", "true").show().addClass("transthis slidedown in reverse");
			} else if (trFlipLeft || trFlipRight) 	{
        		var reverse = trFlipLeft ? " reverse" : "";
       			$('#'+from).attr("active", "false").addClass("transthis flip out" + reverse);
       			$('#'+to).attr("active", "true").show().addClass("transthis flip in" + reverse);
        		// this.doAfterTransition(from, function () {
       			//      from.hide();
       			//      from.attr("class", "");
       			// });
			} else if (trFade) 	{
				$('#'+from).attr("active", "false").addClass("transthis fade out");
       			$('#'+to).attr("active", "true").show().addClass("transthis fade in");
				number = number+1;
       		} else {
        		// just switch
				$('#'+from).attr("class", "transthis");
				$('#'+to).attr("class", "transthis");
				$('#'+to).attr("active", "true").show()
				$('#'+from).attr("active", "false").hide()
   			}
				// set new current view
				from = to;
			}
		}
}