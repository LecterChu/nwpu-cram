// Used for dW e-mail to a friend function
// Grab only the title from the entire document.title value
function dWSplitChar(ch, str) {
    var start = 0;
    var splits = new Object;
    var end;
    var i = 0;
    while (start < str.length) {
        end = start;
        while (end < str.length &&
               ch.indexOf(str.charAt(end)) < 0) {
            end++;
        }
        splits[i++] = str.substring(start,end);
        start = end + 1;
    }
    splits.length = i;
    return splits;
}

function getTitle(){
    var j=0;
    var titlestring="";
    var splitfields = dWSplitChar(':', document.title);
    if (splitfields.length>2) {
        for (j=2;j<splitfields.length;j++) {
            if (j!=2) {
                titlestring+=": ";
            }
            titlestring+=splitfields[j];
        }
    } else {
        titlestring=document.title;
    }
    return titlestring;
}

var justTitle = getTitle();
