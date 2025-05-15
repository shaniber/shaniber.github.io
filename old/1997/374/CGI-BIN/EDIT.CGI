#!/usr/local/bin/perl

use CGI;
use Msql;

$cgiquery = new CGI;
$server = "alf.usask.ca";
$database = "cmpt374group11";
$dbproc = Connect Msql $server, $database||print "Cannot connect to server";

print "Content-type:text/html\n\n";
print <<ENDOFTEXT;
<html>
<head>
  <title>Query results</title>
</head>
<body bgcolor="#fafbfa">
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
<a href="../search.html">search</a>&nbsp;
<a href="../add.html">add</a>&nbsp;
<a href="../edit.html">edit</a>&nbsp;
<a href="../delete.html">delete</a>
<p>
ENDOFTEXT
;

$querytype = $cgiquery->param('qtype');
$querystring = $cgiquery->param('qstr');
$queryopt = $cgiquery->param('qopt');

if ($queryopt eq "substr") {
  $querystring = "%".$querystring."%";
}

$querystring = uc($querystring);

$sql = "Select distinct ALBUM.ALBUM_NO, ALBUM.ALBUM_NAME, 
                        ALBUM.GROUP_NAME, LABEL.LABEL_NAME, 
                        ALBUM.NO_TRACKS 
        from ALBUM, LABEL
        where ALBUM.LABEL_NO = LABEL.LABEL_NO ";

if ($querytype eq "bygroup") {
  $sql = $sql . "and ALBUM.GROUP_NAME like '$querystring'";
}
elsif ($querytype eq "byalbum") {
  $sql = $sql . "and ALBUM.ALBUM_NAME like '$querystring'";
}
elsif ($querytype eq "bylabel") {
  $sql = $sql . "and LABEL.LABEL_NAME like '$querystring'";
}
elsif ($querytype eq "bysong") {
  $sql = "Select distinct ALBUM.ALBUM_NO, ALBUM.ALBUM_NAME,
            ALBUM.GROUP_NAME, LABEL.LABEL_NAME, ALBUM.NO_TRACKS
            from ALBUM, LABEL, TRACK_TITLES 
            where TRACK_TITLES.TRACK_TITLE like '$querystring'
              and ALBUM.ALBUM_NO=TRACK_TITLES.ALBUM_NO
              and ALBUM.LABEL_NO=LABEL.LABEL_NO";
}

$sth = Query $dbproc $sql||print "Cannot do query<BR>\n";

$nr = $sth->numrows;

if ($nr==0) {
  print "No results returned<BR>";
}
else {
  print <<ENDOFTEXT;
  <table border=2>
    <tr bgcolor="#cccccc">
      <th>Group</th>
      <th>Album</th>
      <th>Command</th>
    </tr>
ENDOFTEXT
;
  @arr = FetchRow $sth;
  while (@arr!=()) {
    print <<ENDOFTEXT;
    <tr bgcolor="#fff8dc">
      <td>$arr[2]</td>
      <td>$arr[1]</td>
      <td><a href="do_edit.cgi?album_id=$arr[0]">Edit album</a></td>
    </tr>
ENDOFTEXT
;
    @arr = FetchRow $sth;
  }

print "</table>";
print "<p><center><a href=\"../index.html\">Go Main</a></center>";
}
print "</body></html>";

