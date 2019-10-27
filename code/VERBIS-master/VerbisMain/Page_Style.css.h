#ifndef PAGE_STYLE_CSS_H
#define PAGE_STYLE_CSS_H

const char PAGE_Style_css[] PROGMEM = R"=====(
body { color: #000000; font-family: avenir, helvetica, arial, sans-serif;  letter-spacing: 0.15em;} 
hr {    background-color: #eee;    border: 0 none;   color: #eee;    height: 1px; } 
.btn, .btn:link, .btn:visited {  
	border-radius: 0.3em;  
	border-style: solid;  
	border-width: 1px;  
color: #111;  
display: inline-block;  
	font-family: avenir, helvetica, arial, sans-serif;  
	letter-spacing: 0.15em;  
	margin-bottom: 0.5em;  
padding: 1em 0.75em;  
	text-decoration: none;  
	text-transform: uppercase;  
	-webkit-transition: color 0.4s, background-color 0.4s, border 0.4s;  
transition: color 0.4s, background-color 0.4s, border 0.4s; 
} 
.btn:hover, .btn:focus {
color: #7FFFDB;  
border: 1px solid #7FFFDB;  
	-webkit-transition: background-color 0.3s, color 0.3s, border 0.3s;  
transition: background-color 0.3s, color 0.3s, border 0.3s; 
}
	.btn:active {  
color: #00D974;  
border: 1px solid #00D974;  
		-webkit-transition: background-color 0.3s, color 0.3s, border 0.3s;  
transition: background-color 0.3s, color 0.3s, border 0.3s; 
	} 
	.btn--s 
	{  
		font-size: 12px; 
	}
	.btn--m { 
		font-size: 14px; 
	}
	.btn--l {  
		font-size: 20px;  border-radius: 0.25em !important; 
	} 
	.btn--full, .btn--full:link {
		border-radius: 0.25em; 
display: block;  
			margin-left: auto; 
			margin-right: auto; 
			text-align: center; 
width: 100%; 
	} 
	.btn--blue:link, .btn--blue:visited {
color: #fff;  
		background-color: #00D974; 
	}
	.btn--blue:hover, .btn--blue:focus {
color: #fff !important;  
		background-color: #00AA63;  
		border-color: #00AA63; 
	}
	.btn--blue:active {
color: #fff; 
		background-color: #003F1F;  border-color: #003F1F; 
	}
	@media screen and (min-width: 32em) {
		.btn--full {  
			max-width: 16em !important; } 
	}
)=====";

#endif
