<?php
    $fileNeedToShow = $_REQUEST["file"];
    //echo $fileNeedToShow;
    system("./article_analize.run ".$fileNeedToShow);
?>