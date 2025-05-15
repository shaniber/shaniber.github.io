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

for ($i=0;$i<$numtracks;$i++) {
  $track[$i] = $cgiquery->param("track$i");
  $ttime[$i] = $cgiquery->param("ttime$i");
}

print "Content-type:text/html\n\n";

$dbproc = Connect Msql $server, $database||print "Cannot connect to server<BR>";

# update track titles
$sql = "delete from TRACK_TITLES where ALBUM_NO = $album_id";
$sth = Query $dbproc $sql||print "Cannot do query<BR>\n";

for ($i=1;$i<=$numtracks;$i++) {
  if ($track[$i-1] ne "") {
    $sql = "insert into TRACK_TITLES 
                   (ALBUM_NO, TRACK_NO, TRACK_TITLE, TRACK_TIME)
                   values ($album_id,$i,'$track[$i-1]','$ttime[$i-1]')";
    $sth[$i] = Query $dbproc $sql||print "Cannot do query<BR>\n";
  }
}

$sql = "select GROUP_NAME from ALBUM where ALBUM_NO=$album_id";
$sth = Query $dbproc $sql||print "Cannot do query";
@arr = FetchRow $sth;
$oldgroupname = $arr[0];

# update group info
if ($oldgroupname ne $group) {
  $sql = "update GROUP_NAMES set GROUP_NAME='$group' 
          where GROUP_NAME='$oldgroupname'";
  $sth = Query $dbproc $sql||print "Cannot do query";
}
$sql = "update GROUP_NAMES set GENRE='$genre' where GROUP_NAME='$group'";
$sth = Query $dbproc $sql||print "Cannot do query";

# update ALBUM
$sql = "update ALBUM set ALBUM_NAME='$album' where ALBUM_NO=$album_id";
$sth = Query $dbproc $sql||print "Cannot do query";

$sql = "update ALBUM set GROUP_NAME='$group' where ALBUM_NO=$album_id";
$sth = Query $dbproc $sql||print "Cannot do query";

$sql = "update ALBUM set NO_TRACKS=$numtracks where ALBUM_NO=$album_id";
$sth = Query $dbproc $sql||print "Cannot do query";

# update LABEL
$sql = "Select LABEL_NO from ALBUM where ALBUM_NO=$album_id";
$sth = Query $dbproc $sql||print "Cannot do query";
@arr = FetchRow $sth;
$labelno = $arr[0];

$sql = "update LABEL set LABEL_NAME='$label' where LABEL_NO=$labelno";
$sth = Query $dbproc $sql||print "Cannot do query";

$sql = "update LABEL set LOCATION='$labelloc' where LABEL_NO=$labelno";
$sth = Query $dbproc $sql||print "Cannot do query";

# update group url
if ($groupurl) {
  $sql = "Select URL_NO from GROUP_URLS where GROUP_NAME='$oldgroupname'";
  $sth = Query $dbproc $sql||print "Cannot do query";
  @arr = FetchRow $sth;
  if (@arr!=()) {
    $sql = "Update GROUP_URLS set GROUP_NAME='$group' where URL_NO=$arr[0]";
    $sth = Query $dbproc $sql||print "Cannot do query";
    $sql = "Update GROUP_URLS set URL='$groupurl' where URL_NO=$arr[0]";
    $sth = Query $dbproc $sql||print "Cannot do query";
  }
  else {
    $sql = "Select * from GROUP_URLS order by URL_NO";
    $sth = Query $dbproc $sql||print "Cannot do query";
    $sth->dataseek($sth->numrows);
    @arr = FetchRow $sth;
    if (@arr!=()) {
      $newurlno = $arr[0] + 1;
    }
    else {
      $newurlno = 1;
    }
    $sql = "Insert into GROUP_URLS values ($newurlno, '$group', '$groupurl')";
    $sth = Query $dbproc $sql||print "Cannot do query";
  }
}
else {
  $sql = "Delete from GROUP_URLS where GROUP_NAME = '$oldgroupname'";
  $sth = Query $dbproc $sql||print "Cannot do query";
}

# update sound url
if ($soundurl) {
  $sql = "Select ID_NO from SOUNDS where ALBUM_NO=$album_id";
  $sth = Query $dbproc $sql||print "Cannot do query";
  @arr = FetchRow $sth;
  if (@arr!=()) {
    $sql = "Update SOUNDS set ALBUM_NO=$album_id where ID_NO=$arr[0]";
    $sth = Query $dbproc $sql||print "Cannot do query";
    $sql = "Update SOUNDS set SOUND_FILE_LOCATION='$soundurl' 
            where ID_NO=$arr[0]";
    $sth = Query $dbproc $sql||print "Cannot do query";
  }
  else {
    $sql = "Select * from SOUNDS order by ID_NO";
    $sth = Query $dbproc $sql||print "Cannot do query";
    $sth->dataseek($sth->numrows);
    @arr = FetchRow $sth;
    if (@arr!=()) {
      $newurlno = $arr[0] + 1;
    }
    else {
      $newurlno = 1;
    }
    $sql = "Insert into SOUNDS values ($newurlno, $album_id, '$soundurl')";
    $sth = Query $dbproc $sql||print "Cannot do query";
  }
}
else {
  $sql = "Delete from SOUNDS where ALBUM_NO = $album_id";
  $sth = Query $dbproc $sql||print "Cannot do query";
}

$newurl = "search.cgi?qtype=bynum&qstr=$album_id&qopt=fullstr";
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
CD information for $group/$album has been updated.<p>
<a href="$newurl">Go here to see the updated information</a>
</body>
</html>
ENDOFTEXT
;

