<style type="text/css">
#myArmory { margin: 0 auto; text-align: center; }
#charName a { font-size:120%; font-weight:bold; color:#ffcc00; }
#charTitle { font-size:110%; color:#dddddd; }
.toon_layer {display:none;}
.toon_layer object, .charBoxBar { outline: 0; }
</style>
<div id="myArmory"></div>
<script src="http://www.wowhead.com/widgets/power.js"></script>
<script src="http://www.axiomfiles.com/Files/258012/armory-min.js" type="text/javascript"></script>
<script type="text/javascript">
var char = [];
// Add more characters as follows
// char.push(['NAME','TITLE','3D ARMORY INFO','IMAGE OR TEXT LINK']);

char.push(['Girlwood','Guild Leader','http://www.3darmory.com/us/Ghostlands/girlwood','<img src="ttmm.guildportal.com/GuildImages/WOWRosterImages/Paladin.gif">']);
char.push(['Reactant','Randome Mage','http://www.3darmory.com/us/Ghostlands/reactant','<img src="ttmm.guildportal.com/GuildImages/WOWRosterImages/Mage.gif">']);
char.push(['Bootysweatt','Officer','http://www.3darmory.com/us/Ghostlands/bootysweatt','<img src="ttmm.guildportal.com/GuildImages/WOWRosterImages/Rogue.gif">']);

$('#myArmory').armory(char);
</script>


<style type="text/css">
/* overall box style */
.recruitTitle { text-align: center; font-size:130%; }
#recruitTalent { margin: 0 auto; width: 200px; }

/* color used in tooltips (works for text and background) */
.high { color: #0f0; }
.medium { color: #ff0; }
.low { color: #f00; }
.none { color: #999; }

/* text color when colorBackground is true */
.usebg { color: #000; }

/* opacity used on images */
img.high { opacity: 1; filter: alpha(opacity=100); }
img.medium { opacity: .75; filter: alpha(opacity=75); }
img.low { opacity: .5; filter: alpha(opacity=50); }
img.none { opacity: .25; filter: alpha(opacity=25); }

/* ".classIcon" contains the icon and text, ".classIcon span" only contains the class name text */
.classIcon { width: 60%; }
.classIcon span { padding-left: 5px; }

/* contains all 3 talent tree icons */
.talentIcons { width: 40%; text-align: right; }
.classIcon img, .talentIcons img { vertical-align: top; }
</style>

<div class="recruitTitle"> Recruitment Needs</div>
<div id="recruitTalent"></div>

<script src="http://www.axiomfiles.com/Files/258012/talents-min.js" type="text/javascript"></script>
<script type="text/javascript">
$(document).ready(function(){
 recruitByTalent();
})
</script>

