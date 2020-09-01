/* Theme Stuff */
jQuery(document).ready(function () {
    jQuery("head").append("<link rel='stylesheet' type='text/css' href='/collections/sites/all/libraries/utk/splashstyle.css'>");
    var collectionname = jQuery("#splashintrotext").attr('href');

    /* Collection Dropdown Selector */
    if (collectionname == '/collections/derriscollection') {
        jQuery(("option[value='gsmrc:derris']")).prependTo("#edit-collection-select");
        jQuery(("option[value='gsmrc:derris']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/scopescollection') {
        jQuery(("option[value='collections:scopes']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:scopes']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/cdanielcartooncollection') {
        jQuery(("option[value='collections:cDanielCartoon']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:cDanielCartoon']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/sanbornmapcollection') {
        jQuery(("option[value='collections:sanborn']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:sanborn']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/kintnercollection') {
        jQuery(("option[value='gsmrc:kintner']")).prependTo("#edit-collection-select");
        jQuery(("option[value='gsmrc:kintner']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/50yrcovecollection') {
        jQuery(("option[value='gsmrc:50yrcove']")).prependTo("#edit-collection-select");
        jQuery(("option[value='gsmrc:50yrcove']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/adamscollection') {
        jQuery(("option[value='gsmrc:adams']")).prependTo("#edit-collection-select");
        jQuery(("option[value='gsmrc:adams']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/postcardcollection') {
        jQuery(("option[value='gsmrc:pcard00']")).prependTo("#edit-collection-select");
        jQuery(("option[value='gsmrc:pcard00']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/bakercollection') {
        jQuery(("option[value='collections:mpabaker']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:mpabaker']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/kefauvercollection') {
        jQuery(("option[value='collections:kefauver']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:kefauver']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/wccochrancollection') {
        jQuery(("option[value='gsmrc:wcc']")).prependTo("#edit-collection-select");
        jQuery(("option[value='gsmrc:wcc']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/webstercollection') {
        jQuery(("option[value='gsmrc:webster']")).prependTo("#edit-collection-select");
        jQuery(("option[value='gsmrc:webster']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/alumnuscollection') {
        jQuery(("option[value='collections:alumnus']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:alumnus']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/heilmancollection') {
        jQuery(("option[value='collections:heilman']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:heilman']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/hikingclub') {
        jQuery(("option[value='gsmrc:smhc']")).prependTo("#edit-collection-select");
        jQuery(("option[value='gsmrc:smhc']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/edgamblecollection') {
        jQuery(("option[value='collections:gamble']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:gamble']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/commencementscollection') {
        jQuery(("option[value='collections:utkcomm']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:utkcomm']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/basscollection') {
        jQuery(("option[value='collections:bass']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:bass']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/cdfcollection') {
        jQuery(("option[value='collections:cdf']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:cdf']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/volvoices') {
        jQuery(("option[value='collections:volvoices']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:volvoices']")).attr('selected', 'selected');
    }
    if (collectionname == '/collections/crimedocuments') {
        jQuery(("option[value='collections:ekcd']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:ekcd']")).attr('selected', 'selected');
    }

    /* Ugh--the above won't work if we use the New Menu Options for the Splash Pages so here */
    collectionname = jQuery("#splash-logo").attr('alt');
    if (collectionname == 'Banner Image for the William Derris Slide Collection') {
        jQuery(("option[value='gsmrc:derris']")).prependTo("#edit-collection-select");
        jQuery(("option[value='gsmrc:derris']")).attr('selected', 'selected');
    }
    if (collectionname == 'WWII Oral History Collection Banner Image') {
        jQuery(("option[value='collections:wwiioh']")).prependTo("#edit-collection-select");
        jQuery(("option[value='collections:wwiioh']")).attr('selected', 'selected');
    }


    /* ID Images in Content */
    jQuery("#leftside > img").attr('id', 'splashpageimg');
    jQuery("#rightside > img").attr('id', 'splashpageimg');
});
