/* Global XML HTTP variable.  Can be used to allow callbacks easy access to return values. */
var xmlhttp;
var xmlhttp2;

// Popup window code
function newPopup(url) {
	popupWindow = window.open(
		url,'popUpWindow','height=200,width=800,left=10,top=10,resizable=yes,scrollbars=yes,toolbar=no,menubar=no,location=no,directories=no,status=yes')
}

function validate_email(id1, id2)
{
	var x = document.getElementById(id1).value;
	
	if (x != document.getElementById(id2).value)
	{
		alert("Email addresses don't match");
		return false;
	}
	
	var atpos = x.indexOf("@");
	var dotpos = x.lastIndexOf(".");
	if (atpos<1 || dotpos<atpos+2 || dotpos+2>=x.length)
	{
		alert("Not a valid e-mail address");
		return false;
	}
	return true;
}

function clear_input(obj)
{
	obj.value="";
	obj.onclick = null;
	obj.style.color = "black";
	obj.style.fontStyle = "normal";
}

function kill_me_via_grandparent(node)
{
	node.parentNode.parentNode.removeChild(node.parentNode);
}

function kill_me_via_parent(node)
{
	node.parentNode.removeChild(node.parentNode);
}

function column_to_list(table_id, col_num, ps_id, name, hidden_list)
{	
	hide_column(table_id, col_num);
	//alert(hidden_list);
	list = document.getElementById(hidden_list);
	list.innerHTML += "<span>[<a href=\"javascript:void(0)\" onClick=\"javascript:list_to_column(" + table_id + ", " + col_num + ", " + ps_id + ", this)\">Show " + name + "</a>]</span> ";	
	
	post("do_toggle_grade_column.php", "ps_id", ps_id);
}

function list_to_column(table_id, col_num, ps_id, node)
{	
	//alert(node.innerHTML);
	hide_column(table_id, col_num);
	kill_me_via_grandparent(node);
	post("do_toggle_grade_column.php", "ps_id", ps_id);
}

function hide_column(table_id, col_num)
{			
	table = document.getElementById(table_id);		
	for (counter = 0; counter < table.rows.length; counter++)
		toggle_visibility_ele(table.rows[counter].cells[col_num]);
}

function validate_file_upload_extension(id)
{
	if (!isSupportedExtension(document.getElementById(id).value))
	{
		alert("Language not supported.  Supported languages: C, C++, C#, Java, Fortran, Racket");
		return false;
	}
	return true;
}

function isSupportedExtension(fileName)
{
	return acceptableExtension(fileName, ['c', 'cpp', 'java', 'txt', 'f', 'for', 'f77', 'f90', 'f95', 'fpp', 'cs', 'rkt', 'ss']);
}

function acceptableExtension( fileName, fileTypes ) 
{	
	if (!fileName) return;

	dots = fileName.split(".")
	//get the part AFTER the LAST period.
	fileType = "." + dots[dots.length-1];

	return fileTypes.join(".").indexOf(fileType) != -1;
}

function resizeIframe(iframeID) 
{ 
	if(self == parent) 
		return false; /* Checks that page is in iframe. */ 
	else if (document.getElementById && document.all) /* Sniffs for IE5+.*/ 
		var FramePageHeight = framePage.scrollHeight + 10; /* framePage is the ID of the framed page's BODY tag. The added 10 pixels prevent an unnecessary scrollbar. */ 
	parent.document.getElementById(iframeID).style.height = FramePageHeight; /* "iframeID" is the ID of the inline frame in the parent page. */ 
} 

/* cookie code */
/* From: http://www.quirksmode.org/js/cookies.html */
function createCookie(name,value,days) {
	if (days) {
		var date = new Date();
		date.setTime(date.getTime()+(days*24*60*60*1000));
		var expires = "; expires="+date.toGMTString();
	}
	else var expires = "";
	document.cookie = name + "=" + escape(value) + expires + "; path=/";
}

function readCookie(name) {
	var nameEQ = name + "=";
	var ca = document.cookie.split(';');
	for(var i=0;i < ca.length;i++) {
		var c = ca[i];
		while (c.charAt(0)==' ') c = c.substring(1,c.length);
		if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
	}
	return null;
}

function eraseCookie(name) {
	createCookie(name,"",-1);
}
/* end cookie code */

function grab(xmlDoc, what)
{
	return xmlDoc.getElementsByTagName(what)[0].childNodes[0].nodeValue;
}

function highlight(div)
{
	div.className = "highlight";
}

function deselect(div)
{
	div.className = "selection";
}

function disableSelection(id)
{
	/*document.getElementById(id).onmousedown=function(){return false};*/
	//document.getElementById(id).style.cursor = "default";
}

//Sample usages
//disableSelection(document.body); //Disable text selection on entire body
//disableSelection(document.getElementById("mydiv")) //Disable text selection on element with id="mydiv"

function select_all_text(element)
{
	text_val = document.getElementById(element.id);
	text_val.focus();
	text_val.select();
}

function prefetchLoader()
{
	loader = new Image();	
	loader.src = "/pics/ajax-loader.gif";
}

function getLoader()
{
	return "<img src=\"/pics/ajax-loader.gif\" width=\"16\" height=\"16\" title=\"Loading...\"/>";
}

function isHidden(id)
{
	return document.getElementById(id).style.display == 'none';
}

function isVisible(id)
{
	return document.getElementById(id).style.display == '';
}

function hide_ele(ele)
{
	ele.style.display = 'none'
}

function show_ele(ele)
{
	ele.style.display = ''
}

function hide(id)
{
	hide_ele(document.getElementById(id));	
}

function show(id)
{
	show_ele(document.getElementById(id));
}

function toggle_visibility_ele(ele)
{
	if (ele.style.display === '')
		hide_ele(ele);
	else
		show_ele(ele);
}

function toggle_visibility(id)
{
	toggle_visibility_ele(document.getElementById(id));
}

/*
	Builds an appropriate XML HTTP instance for the user's browser.
	Returns: An instance of XML HTTP if the browser supports it or null otherwise.	         
*/
function summonAJAXInstance()
{
	/* for IE7+, Firefox, Chrome, Opera, Safari */
	if (window.XMLHttpRequest)
		return xmlhttp = new XMLHttpRequest();
	/* for IE6, IE5 */
	else if (window.ActiveXObject)
		return xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");		
	alert("Your browser does not support XMLHTTP!");
	return null;
}

function getAJAXInstance()
{
	/* for IE7+, Firefox, Chrome, Opera, Safari */
	if (window.XMLHttpRequest)
		return new XMLHttpRequest();
	/* for IE6, IE5 */
	else if (window.ActiveXObject)
		return new ActiveXObject("Microsoft.XMLHTTP");		
	alert("Your browser does not support XMLHTTP!");
	return null;
}

function gather(page, form_id)
{
	if (page != "")
		page = page + "?";
	var form = document.getElementById(form_id);
	/* build form.  e.g. createCourse.php?username=some_user&class_name=COM_SC_121 */
	for (var i = 0; i < form.length; i++)
	{
		/* we only add the ids and values of the fields, not the submit button label */
		type = form.elements[i].type;
		if (type != "submit")
		{	
			/* we only submit checkboxes if they are selected */
			if (!(type == "checkbox" && !form.elements[i].checked))
			{
				page = page + form.elements[i].name + "=" + escape(form.elements[i].value) + "&";
			}
		}
	}
	return page.substring(0, page.length - 1);
}

function gapa(page, html_element, callback)
{
	gather_and_post_async(page, html_element.id, callback);
}

function gather_and_post_async(page, form_id, callback)
{		
	xmlhttp = summonAJAXInstance();	
	if (callback)
		xmlhttp.onreadystatechange = callback;
	//alert(gather(page, form_id));
	xmlhttp.open("POST", gather(page, form_id), true);		
	xmlhttp.send(null);
}

function gather_and_post_async2(page, form_id, callback)
{		
	xmlhttp2 = getAJAXInstance();	
	if (callback)
		xmlhttp2.onreadystatechange = callback;
	//DEBUG: alert(gather(page, form_id));
	xmlhttp2.open("POST", gather(page, form_id), true);		
	xmlhttp2.send(null);
}

function gather_and_post(page, form_id)
{		
	xmlhttp = summonAJAXInstance();	
	xmlhttp.open("POST", gather(page, form_id), false);	
	xmlhttp.send(null);
	location.reload(true);
}

function prompt_gather_post(prompt, page, form_id)
{
	if (confirm(prompt))
		gather_and_post(page, form_id);
}

function blank_callback()
{
	
}

function post(page, property, value)
{
	var xmlhttp = summonAJAXInstance();	
	//alert(page + "?" + property + "=" + value);
	xmlhttp.open("POST", page + "?" + property + "=" + value, true);	
	xmlhttp.send(null);
}

function prompt_and_post(prompt, page, property, value)
{
	if (confirm(prompt))
	{
		var xmlhttp = summonAJAXInstance();	
		xmlhttp.open("POST", page + "?" + property + "=" + value , false);
		xmlhttp.send(null);
		location.reload(true);
	}
}

function load(page, callback)
{
	summonAJAXInstance();	
	/* set callback */
	xmlhttp.onreadystatechange = callback;
	xmlhttp.open("GET", page, true);	
	/* send request */
	xmlhttp.send(null);	
}

function isNumeric(sText)
{
   var ValidChars = "0123456789 ";   

   for (i = 0; i < sText.length; i++) 
   { 
      if (ValidChars.indexOf(sText.charAt(i)) == -1) 
		return false;
   }
   return true;
}

function opacity(id, opacStart, opacEnd, millisec) {
	//speed for each frame
	var speed = Math.round(millisec / 100);
	var timer = 0;

	//determine the direction for the blending, if start and end are the same nothing happens
	if(opacStart > opacEnd) {
		for(i = opacStart; i >= opacEnd; i--) {
			setTimeout("changeOpac(" + i + ",'" + id + "')",(timer * speed));
			timer++;
		}
	} else if(opacStart < opacEnd) {
		for(i = opacStart; i <= opacEnd; i++)
			{
			setTimeout("changeOpac(" + i + ",'" + id + "')",(timer * speed));
			timer++;
		}
	}
}

//change the opacity for different browsers
function changeOpac(opacity, id) {
	var object = document.getElementById(id).style; 
	object.opacity = (opacity / 100);
	object.MozOpacity = (opacity / 100);
	object.KhtmlOpacity = (opacity / 100);
	object.filter = "alpha(opacity=" + opacity + ")";
}

function shiftOpacity(id, millisec) {
	//if an element is invisible, make it visible, else make it ivisible
	if(document.getElementById(id).style.opacity == 0) {
		opacity(id, 0, 100, millisec);
	} else {
		opacity(id, 100, 0, millisec);
	}
}

function blendimage(divid, imageid, imagefile, millisec) {
	var speed = Math.round(millisec / 100);
	var timer = 0;
	
	//set the current image as background
	document.getElementById(divid).style.backgroundImage = "url(" + document.getElementById(imageid).src + ")";
	
	//make image transparent
	changeOpac(0, imageid);
	
	//make new image
	document.getElementById(imageid).src = imagefile;

	//fade in image
	for(i = 0; i <= 100; i++) {
		setTimeout("changeOpac(" + i + ",'" + imageid + "')",(timer * speed));
		timer++;
	}
}

function currentOpac(id, opacEnd, millisec) {
	//standard opacity is 100
	var currentOpac = 100;
	
	//if the element has an opacity set, get it
	if(document.getElementById(id).style.opacity < 100) {
		currentOpac = document.getElementById(id).style.opacity * 100;
	}

	//call for the function that changes the opacity
	opacity(id, currentOpac, opacEnd, millisec)
}

/* Debug functions */
/*
	Delivers a message box to the user with the response text from the server.
*/
function DEBUG_printf_response()
{
	if (xmlhttp.readyState==4)
		alert("back! server: " + xmlhttp.responseText);
}