ImageMagick
===========

This module provides ImageMagick integration.

Installation
------------

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules.

- Go to Administration > Configuration > Media > Image toolkit 
  (admin/config/media/image-toolkit) and change the image toolkit to ImageMagick.

- If the convert binary cannot be found in the default shell path, you need to
  enter the full path to ImageMagick's convert executable, including the
  filename itself.

Requirements
-------------

- ImageMagick (http://www.imagemagick.org) needs to be installed on your server
  and the convert binary needs to be accessible and executable from PHP.

- The PHP configuration must allow invocation of proc_open() (which is
  security-wise identical to exec()).

Consult your server administrator or hosting provider if you are unsure about
these requirements.

Issues
------

Bugs and Feature requests should be reported in the Issue Queue:
https://github.com/backdrop-contrib/imagemagick/issues.

Current Maintainers
-------------------

- Jen Lampton (https://github.com/jenlampton).

Credits
-------

- Ported to Backdrop CMS by Kevin Thull (https://github.com/kthull).
- Originally written for Drupal by Daniel F. Kudwien ("sun", http://drupal.org/user/54136).

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.
