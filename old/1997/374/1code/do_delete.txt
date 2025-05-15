#!/usr/local/bin/perl

use CGI; 
use Msql;

$cgiquery = new CGI;
$server = "alf.usask.ca";
$database = "cmpt374group11";

print $cgiquery->header;
$dbproc = Msql->connect($server, $database)||print"Connect failed";


#
# retrieve variables from the form

$number = $cgiquery->param('album_id');

$query = "select * from ALBUM where ALBUM_NO = $number";
$res = $dbproc->query($query)||print "number=ALBUM query failed<BR>\n";


@row = $res->fetchrow;
$albnum = $row[0];
$album = $row[1];
$artist = $row[2];
$label_no = $row[3];

$query=  "select * from ALBUM where GROUP_NAME = '$artist'";
$res = $dbproc->query($query)||print "artist=ALBUM query failed<BR>\n";

$numrows = $res->numrows;

#	if last record in album for this artist delete from the following
#	GROUP_NAMES, GROUP_URLS, LABEL

if ($numrows eq 1){
	$sql=  "delete from GROUP_NAMES where GROUP_NAME = '$artist'";
	$sth = $dbproc->query($sql)||print "GROUP NAMES delete failed<BR>\n";

	$sql=  "delete from GROUP_URLS where GROUP_NAME = '$artist'";
	$sth = $dbproc->query($sql)||print "GROUP_URLS delete failed<BR>\n";
}

$sql=  "delete from LABEL where LABEL_NO = $label_no";
$sth = $dbproc->query($sql)||print "LABEL delete failed<BR>\n";

$sql = "delete from ALBUM where ALBUM_NO = $number";
$sth = $dbproc->query($sql)||print "ALBUM delete failed<BR>\n";

$sql = "delete from SOUNDS where ALBUM_NO = $number";
$sth = Query $dbproc $sql||print "SOUNDS delete failed<BR>\n";

$sql = "delete from TRACK_TITLES where ALBUM_NO = $number";
$sth = $dbproc->query($sql)||print "TRACK_TITLES delete failed<BR>\n";

print "<Content-type:text/html\n\n>";
#print"<html><head><title>DELETE RESULT</title></head>";
print "\n";
print "<FONT SIZE=+2>";
print "<body>";
print "\n";
print"<BR><center>";
print "Deleted CD";
print "<br>";
print "CD number : $albnum";
print "<BR>";
print "Album Name : $album";
print "<BR>";
print "Group/Artist : $artist";
print "<BR>";
#print "<p><center><a href=\"../delete.html\">Back to Delete</a></center>";
print "<p><a href=\"../delete.html\">Back to Delete</a></center>";
print "</FONT></body></html>";
print $cgiquery->end_html;
