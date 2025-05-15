#!/usr/local/bin/perl

use CGI;
use Msql;

$cgiquery = new CGI;
$server = "alf.usask.ca";
$database = "cmpt374group11";

print "Content-type:text/html\n\n";
$dbproc = Connect Msql $server, $database||print "Cannot connect to server";

$querytype = $cgiquery->param('qtype');
$querystring = $cgiquery->param('qstr');
$queryopt = $cgiquery->param('qopt');

if ($queryopt eq "substr") {
  $querystring = "%".$querystring."%";
}

$querystring = uc($querystring);

$sql = "Select distinct ALBUM.ALBUM_NO, ALBUM.ALBUM_NAME, 
                        ALBUM.GROUP_NAME, LABEL.LABEL_NAME, ALBUM.NO_TRACKS, 
                        LABEL.LOCATION
        from ALBUM, LABEL
        where ALBUM.LABEL_NO = LABEL.LABEL_NO ";

if ($querytype eq "bynum") {
  $sql = $sql . "and ALBUM.ALBUM_NO = $querystring";
}
elsif ($querytype eq "bygroup") {
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
            ALBUM.GROUP_NAME, LABEL.LABEL_NAME, ALBUM.NO_TRACKS,
            LABEL.LOCATION
            from ALBUM, LABEL, TRACK_TITLES 
            where TRACK_TITLES.TRACK_TITLE like '$querystring'
              and ALBUM.ALBUM_NO=TRACK_TITLES.ALBUM_NO
              and ALBUM.LABEL_NO=LABEL.LABEL_NO";
}
elsif ($querytype eq "bygenre") {
  $sql = "Select distinct ALBUM.ALBUM_NO, ALBUM.ALBUM_NAME,
            ALBUM.GROUP_NAME, LABEL.LABEL_NAME, ALBUM.NO_TRACKS,
            LABEL.LOCATION
          from ALBUM, LABEL, GROUP_NAMES
          where GROUP_NAMES.GENRE like '$querystring'
            and ALBUM.GROUP_NAME = GROUP_NAMES.GROUP_NAME
            and ALBUM.LABEL_NO = LABEL.LABEL_NO";
}

$sth = Query $dbproc $sql||print "Cannot do query<BR>\n";

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
ENDOFTEXT
;

$nr = $sth->numrows;
#print "$nr rows returned<BR>";

if ($nr == 0) {
  print "No results returned<BR>";
}
elsif ($nr == 1) {
  @arr = FetchRow $sth;
  print <<ENDOFTEXT;
    <table border=2>
      <tr>
        <td bgcolor="#cccccc">Group</td>
ENDOFTEXT
;
  $sql2 = "Select GROUP_URLS.URL from GROUP_URLS
           where GROUP_URLS.GROUP_NAME='$arr[2]'";
  $sth2 = Query $dbproc $sql2;
  @arr2 = FetchRow $sth2;
  if (@arr2!=()) {
    print "<td bgcolor=\"#fff8dc\"><a href=\"$arr2[0]\">$arr[2]</a></td>";
  }
  else {
    print "<td bgcolor=\"#fff8dc\">$arr[2]</td>";
  }
  print <<ENDOFTEXT;
      </tr>
      <tr>
        <td bgcolor="#cccccc">Album</td>
ENDOFTEXT
;
  $sql3 = "Select SOUNDS.SOUND_FILE_LOCATION from SOUNDS
           where SOUNDS.ALBUM_NO = $arr[0]";
  $sth3 = Query $dbproc $sql3;
  @arr3 = FetchRow $sth3;
  print "        <td bgcolor=\"fff8dc\">$arr[1]";
  if (@arr3!=()) {
    print "<a href=\"$arr3[0]\"><img border=0 src=\"../images/sound.jpg\" 
alt=\"yes\"></a>";
  }
  print "        </td>";

  print <<ENDOFTEXT;
      </tr>
      <tr>
        <td bgcolor="#cccccc">Label</td>
        <td bgcolor="#fff8dc">$arr[3] ($arr[5])</td>
      </tr>
      <tr>
        <td bgcolor="#cccccc">Number of tracks</td>
        <td bgcolor="#fff8dc">$arr[4]</td>
      </tr>
      <tr>
        <td bgcolor="#cccccc">Track listing</td>
        <td bgcolor="#fff8dc">
ENDOFTEXT
;
  $sql2 = "Select TRACK_TITLES.TRACK_TITLE, TRACK_TITLES.TRACK_TIME,
                  TRACK_TITLES.TRACK_NO
           from TRACK_TITLES
           where TRACK_TITLES.ALBUM_NO=$arr[0]
           order by TRACK_TITLES.TRACK_NO";
  $sth2 = Query $dbproc $sql2;
  @arr2 = FetchRow $sth2;
  while (@arr2!=()) {
    print "$arr2[0] ($arr2[1])<br>";
    @arr2 = FetchRow $sth2;
  }
  print <<ENDOFTEXT;
        </td>
      </tr>
ENDOFTEXT
;
}
else {
  @arr = FetchRow $sth;  
  print <<ENDOFTEXT;
    <table border=2>
      <tr bgcolor="cccccc">
        <th>Group</th>
        <th>Album</th>
        <th>Label (Location)</th>
        <th>Tracks</th>
        <th>More info</th>
        <th>Sound clip</th>
      </tr>
ENDOFTEXT
;
  while (@arr!=()) {
    print "<tr bgcolor=\"#fff8dc\">";
    $sql2 = "Select GROUP_URLS.URL from GROUP_URLS
             where GROUP_URLS.GROUP_NAME='$arr[2]'";
    $sth2 = Query $dbproc $sql2;
    @arr2 = FetchRow $sth2;
    if (@arr2!=()) {
      print "<td><a href=\"$arr2[0]\">$arr[2]</a></td>";
    }
    else {
      print "<td>$arr[2]</td>";
    }
    print <<ENDOFTEXT;
        <td>$arr[1]</td>
        <td>$arr[3] ($arr[5])</td>
        <td>$arr[4]</td>
        <td><a href="tracks.cgi?album_id=$arr[0]">Track listing</a></td>
        <td>&nbsp;&nbsp;&nbsp;
ENDOFTEXT
;
  $sql3 = "Select SOUNDS.SOUND_FILE_LOCATION from SOUNDS
           where SOUNDS.ALBUM_NO = $arr[0]";
  $sth3 = Query $dbproc $sql3;
  @arr3 = FetchRow $sth3;
  if (@arr3!=()) {
    print "<a href=\"$arr3[0]\"><img border=0 src=\"../images/sound.jpg\" 
alt=\"yes\"></a>";
  }
  print "        </td>";
  print "      </tr>";
  @arr = FetchRow $sth;
  }
}
print "</table><p><center><a href=\"../index.html\">Go 
Main</a></p></center>";

print $cgiquery->end_html;
