#!/usr/local/bin/perl

use CGI;
use Msql;

$cgiquery = new CGI;
$server = "alf.usask.ca";
$database = "cmpt374group11";

print "Content-type:text/html\n\n";

$album_id = $cgiquery->param('album_id');

$dbproc = Connect Msql $server, $database||print "Cannot connect to server";

$sql = "Select distinct ALBUM.GROUP_NAME, ALBUM.ALBUM_NAME
        from ALBUM
        where ALBUM.ALBUM_NO=$album_id";

$sth = Query $dbproc $sql||print "Cannot do query<BR>\n";
@arr = FetchRow $sth;
$artist = $arr[0];
$album = $arr[1];

print <<ENDOFTEXT;
<html>
<head>
  <title>Track listing for $album</title>
</head>
<body bgcolor="#ffffff">
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
Track listing for $artist/$album<p>
ENDOFTEXT
;

$sql = "Select TRACK_TITLES.TRACK_TITLE, TRACK_TITLES.TRACK_TIME
        from TRACK_TITLES
        where TRACK_TITLES.ALBUM_NO=$album_id";
$sth = Query $dbproc $sql||print "Cannot do query<BR>\n";

$nr = $sth->numrows;
if ($nr == 0) {
  print "No track listing for this CD<BR>\n";
}
else {
  @arr = FetchRow $sth;
  print <<ENDOFTEXT;
    <table border=2>
      <tr bgcolor="#cccccc">
        <th>Track name</th>
        <th>Track time</th>
      </tr>
ENDOFTEXT
;
  while (@arr!=()) {
    print <<ENDOFTEXT;
      <tr bgcolor="#fff8dc">
        <td>$arr[0]</td>
        <td>$arr[1]</td>
      </tr>
ENDOFTEXT
;
  @arr = FetchRow $sth;
  }
}
print "</table>";
print "</center>";
print "</body></html>\n";

