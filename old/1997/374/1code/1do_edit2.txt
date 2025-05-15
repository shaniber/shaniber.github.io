#!/usr/local/bin/perl

use CGI;
use Msql;

$cgiquery = new CGI;
$server = "alf.usask.ca";
$database = "cmpt374group11";

$album_id = $cgiquery->param('album_id');
$group = $cgiquery->param('group');
$genre = $cgiquery->param('genre');
$album = $cgiquery->param('album');
$label = $cgiquery->param('label');
$labelloc = $cgiquery->param('labelloc');
$numtracks = $cgiquery->param('numtracks');
$soundurl = $cgiquery->param('soundurl');
$groupurl = $cgiquery->param('groupurl');

print "Content-type:text/html\n\n";

print <<ENDOFTEXT;
<html>
<head>
  <title>Query results</title>
</head>
<body bgcolor="#ffffff">
<font face="arial,helvetica" size=+1>
<center>
<map name="map1">
<area shape="rect" coords="0,50,125,81" href="../search.html" alt="search">
<area shape="rect" coords="140,50,205,81" href="../add.html" alt="add">
<area shape="rect" coords="220,50,280,81" href="../edit.html" alt="edit">
<area shape="rect" coords="300,50,412,81" href="../delete.html" alt="delete">
</map>
<img width=412 height=81 border=0 src="../images/buttonbar.jpg" 
usemap="#map1" ismap> <p>
<a href="../search.html">search</a>
<a href="../add.html">add</a>
<a href="../edit.html">edit</a>
<a href="../delete.html">delete</a>
<p>
<form method="post" action="do_edit3.cgi">
<input type="hidden" name="album_id" value="$album_id">
<input type="hidden" name="group" value="$group">
<input type="hidden" name="genre" value="$genre">
<input type="hidden" name="album" value="$album">
<input type="hidden" name="label" value="$label">
<input type="hidden" name="labelloc" value="$labelloc">
<input type="hidden" name="numtracks" value="$numtracks">
<input type="hidden" name="soundurl" value="$soundurl">
<input type="hidden" name="groupurl" value="$groupurl">
<table border=2>
  <tr bgcolor="#cccccc">
    <th>Track title</th>
    <th>Track time</th>
  </tr>
ENDOFTEXT
;

$badform = 0;
if ($group eq "") {
  print "Group artist name field missing<br>\n";
  $badform=1;
}
if ($album eq "") {
  print "Album name field missing<br>\n";
  $badform=1;
}
if ($label eq "") {
  print "Label field missing<br>\n";
  $badform=1;
}
if ($badform!=0) {
  print "Please go back and enter the missing field(s)<br>\n";
} 
else {

$dbproc = Connect Msql $server, $database;

$sql = "Select TRACK_TITLES.TRACK_TITLE, TRACK_TITLES.TRACK_TIME, 
               TRACK_TITLES.TRACK_NO
         from TRACK_TITLES
         where TRACK_TITLES.ALBUM_NO=$album_id
         order by TRACK_TITLES.TRACK_NO";

$sth = Query $dbproc $sql;
@arr = FetchRow $sth;
$c = 0;
while (@arr!=() && $c < $numtracks) {
  print "  <tr bgcolor=\"#fff8dc\">\n";
  print "    <td><input name=\"track$c\" value=\"$arr[0]\"></td>\n";
  print "    <td><input name=\"ttime$c\" value=\"$arr[1]\"></td>\n";
  print "  </tr>\n";
  @arr = FetchRow $sth;
  $c++;
}
while ($c < $numtracks) {
  print "  <tr bgcolor=\"#fff8dc\">\n";
  print "    <td><input name=\"track$c\"></td>\n";
  print "    <td><input name=\"ttime$c\"></td>\n";
  print "  </tr>\n";
  $c++;
}
print <<ENDOFTEXT;
  <tr>
    <td colspan=2><center><input type="submit" value="submit"></center></td>
  </tr>
</table>
</form>
<center><a href="../index.html">Go Main</a></center>
</body>
</html>
ENDOFTEXT
;
}
