<?php print $doctype; ?>
<html lang="<?php print $language->language; ?>"
      dir="<?php print $language->dir; ?>"<?php print $rdf->version . $rdf->namespaces; ?>>
<head<?php print $rdf->profile; ?>>
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <?php print $head; ?>
    <script>(function (w, d, s, l, i) {
            w[l] = w[l] || [];
            w[l].push({
                'gtm.start':
                    new Date().getTime(), event: 'gtm.js'
            });
            var f = d.getElementsByTagName(s)[0],
                j = d.createElement(s), dl = l != 'dataLayer' ? '&l=' + l : '';
            j.async = true;
            j.src =
                '//www.googletagmanager.com/gtm.js?id=' + i + dl;
            f.parentNode.insertBefore(j, f);
        })(window, document, 'script', 'dataLayer', 'GTM-MB99NS');</script>
    <title><?php print $head_title; ?></title>
    <script crossorigin src="https://unpkg.com/react@16/umd/react.production.min.js"></script>
    <script crossorigin src="https://unpkg.com/react-dom@16/umd/react-dom.production.min.js"></script>
    <noscript>
        <div>HTML menu inserted here for WCAG 2.1 AA accessibility compliance.</div>
    </noscript>
    <?php print $styles; ?>
    <?php print $scripts; ?>
    <!--[if lt IE 9]>
    <script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script>
    <![endif]-->
</head>
<body<?php print $attributes; ?>>
    <div id="skip-link">
        <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
    </div>
    <header id="utk-lib-header"
            data-page-title="Digital Collections"
            data-url="https://digital.lib.utk.edu/"
            data-libchat="e98ae2539f2bd5d1659cc53d7de2812b"></header>
    <?php print render($utk_header); ?>
    <?php print $page_top; ?>
    <?php print $page; ?>
    <?php print $page_bottom; ?>
    <footer id="utk-lib-footer"></footer>
    <script async src="https://www.lib.utk.edu/assets/universal-header.js"></script>
</body>
</html>
