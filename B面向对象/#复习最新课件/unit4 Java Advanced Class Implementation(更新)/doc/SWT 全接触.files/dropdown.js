
// Common redirect function
// Dropdown field must be named "url"
function ibmCommonDropdown(form) {
var value;
if (typeof(form) == "object" && typeof(form.url) == "object") {
value = (form.url[form.url.selectedIndex]).value;
if (value && value != "#") {
window.location.href = value;
}
return false;
}
else {
return true;
}
}
