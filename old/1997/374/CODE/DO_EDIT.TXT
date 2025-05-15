#!/usr/local/bin/perl

use CGI;
use Msql;

$cgiquery = new CGI;
$server = "alf.usask.ca";
$database = "cmpt374group11";

$album_id = $cgiquery->param('album_id');

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
ENDOFTEXT
;

$dbproc = Connect Msql $server, $database||print "Cannot connect to server";

# fetch an URL for the group, if one exists
$sql = "Select distinct GROUP_URLS.URL
        from ALBUM, GROUP_URLS
        where ALBUM.ALBUM_NO = $album_id
          and GROUP_URLS.GROUP_NAME = ALBUM.GROUP_NAME";

$sth = Query $dbproc $sql||print "Cannot do query";
@arr = FetchRow $sth;
$groupurl = $arr[0];

# fetch an URL for a sound from this album, if one exists
$sql = "Select distinct SOUNDS.SOUND_FILE_LOCATION
        from ALBUM, SOUNDS
        where ALBUM.ALBUM_NO = $album_id
          and SOUNDS.ALBUM_NO = $album_id";

$sth = Query $dbproc $sql||print "Cannot do query";
@arr = FetchRow $sth;
$soundurl = $arr[0];

# fetch all the other info
$sql = "Select distinct ALBUM.ALBUM_NO, ALBUM.ALBUM_NAME, 
                        ALBUM.GROUP_NAME, LABEL.LABEL_NAME, ALBUM.NO_TRACKS, 
                        GROUP_NAMES.GENRE, LABEL.LOCATION
        from ALBUM, LABEL, GROUP_NAMES
        where ALBUM.ALBUM_NO = $album_id
          and ALBUM.GROUP_NAME = GROUP_NAMES.GROUP_NAME
          and ALBUM.LABEL_NO = LABEL.LABEL_NO";

$sth = Query $dbproc $sql||print "Cannot do query<BR>\n";

@arr = FetchRow $sth;
print <<ENDOFTEXT;
<form method="post" action="do_edit2.cgi">
  <input type="hidden" name="album_id" value="$album_id">
  <table border=2>
    <tr>
      <th colspan=3>Group/Artist info</th>
    </tr>
    <tr bgcolor="#cccccc">
      <td>Group/artist</td>
      <td>Genre</td>
      <td>URL</td>
    </tr>
    <tr bgcolor="#fff8dc">
      <td><input name="group" value="$arr[2]"></td>
      <td><input name="genre" value="$arr[5]"></td>
      <td><input name="groupurl" value="$groupurl"></td>
    <tr>
    <tr>
      <th colspan=3>Album info</th>
    </tr>
    <tr bgcolor="#cccccc">
      <td>Album</td>
      <td>Label</td>
      <td>Location</td>
    </tr>
    <tr bgcolor="#fff8dc">
      <td><input name="album" value="$arr[1]"></td>
      <td><input name="label" value="$arr[3]"></td>
      <td><input name="labelloc" value="$arr[6]"></td>
    </tr>
    <tr bgcolor="#cccccc">
      <td>Number of tracks</td>
      <td colspan=2>Sound URL</td>
    </tr>
    <tr bgcolor="#fff8dc">
      <td><input name="numtracks" value="$arr[4]"></td>
      <td colspan=2><input name="soundurl" size=42 value="$soundurl"></td>
    </tr>
    <tr>
      <td colspan=3>
        <center>
          <input type="submit" value="submit">
        </center>
      </td>
    </tr> 
  </table>
  </form>
  <p>
  <center><a href="../index.html">Go Main</a></p></center>
</body>
</html>
ENDOFTEXT
;

