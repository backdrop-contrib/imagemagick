<?php
// $Id$

/**
 * Return information about the imagemagick toolkit
 */
function image_imagemagick2_info() {
  return array('name' => 'imagemagick2', 'title' => 'Advanced ImageMagick Toolkit.');
  
}

/**
 * Validate and return toolkit specific settings
 */
function image_imagemagick2_settings() {
$conjure_binary = variable_get('imagemagick2_conjure', '/usr/bin/conjure');


  if(!file_exists($conjure_binary)){
	form_set_error('imagemagick2_conjure',t('%file does not exist or is not executable.',array('%file' => "<em>$conjure_binary</em>")));
  }

	$form['imagemagick2'] = array('#type' => 'fieldset', '#title' => ('Imagemagick2 Settings'));
	$form['imagemagick2']['conjure_binary']=array('#type'=>'textfield',
							'#title' => t('Location of the conjure binary'),'#default_value'=>  variable_get('conjure_binary','/usr/bin/conjure'));
	$form['imagemagick2']['convert_binary']=array('#type'=>'textfield',
							'#title' => t('Location of the convert binary'),'#default_value'=>  variable_get('convert_binary','/usr/bin/convert'));


return $form;

  
}
/* 
Temporary MSL Filename. As we are creating temporary files,
*/

function image_imagemagick2_convert($object){
	$mslfile=start_read_image($object->source);

	if($object->multiple){

		for($i=0;$i<count($object->functioncall);$i++){
			$func="imagemagick2_".$object->functioncall[$i];
			$params=$object->params;

			$mslfile.=$func($params[$i]);
		}
	}
	else{

		$func="imagemagick2_".$object->functioncall;
		$mslfile.=$func($object->params);
	}	
	$mslfile.=close_read_image($object->dest);
	return _imagemagick2_conjure($mslfile);
}

/* Converting the image.module image_resize to image_imagemagick2_convert('resize') */

function image_imagemagick2_resize($source,$dest,$width,$height){
	$convobj=new stdClass();
	$convobj->source=$source;
	$convobj->dest=$dest;
	$convobj->functioncall='resize';
	$convobj->params=array('width'=>$width,'height'=>$height);
	return image_imagemagick2_convert($convobj);
}


function mslfile($mslcontents){
	$i=0;
	$tmp_mslfile='files/tmp/tmp_file_'.$i;
	while(file_exists($tmp_mslfile)){
		$tmp_mslfile='files/tmp/tmp_file_'.$i;
		$i++;
	}
	$fh=fopen($tmp_mslfile,'w');
	fwrite($fh,$mslcontents);
	fclose($fh);
	return $tmp_mslfile;
}

function start_read_image($source){
	$mslfile='<?xml version="1.0" encoding="UTF-8"?>'."\n";
	$mslfile.='<image>'."\n";
	$mslfile.='<read filename="'.$source.'" />'."\n";
	return $mslfile;
}

function close_read_image($dest){
	$mslfile='<write filename="'.$dest.'" />'."\n";
	$mslfile.="</image>";
	return $mslfile;
}


/**
 * Resize an image to the given width and height - Params(width,height)
 */
function imagemagick2_resize($params) {
  $mslfile.='<scale ';
if ($params['width']) 
	$mslfile.='width="'.$params['width'].'" ';
if($params['height'])
	$mslfile.='height="'.$params['height'].'" ';
  $mslfile.='/>';
  return $mslfile;
}

/**
 * Rotate an image - Params (degrees)
 */
function imagemagick2_rotate($params) {
  $mslfile='<rotate degrees="'.$params['degrees'].'"/>';
  return $mslfile;
}

/**
 * Crop an image to the specified dimensions - Params (width,height,x,y)
 */
function imagemagick2_crop($params) {
  $mslfile.='<crop ';
  if($params['width'])
  $mslfile.='width="'.$params['width'].'" ';
  if($height)
  $mslfile.='height="'.$params['height'].'" ';
  if($x)
  $mslfile.='x="'.$params['x'].'" ';
  if($y)
  $mslfile.='y="'.$params['y'].'" ';
  $mslfile.='/>';
  return $mslfile;
}

/*
* Blur an Image - Params('radius','sigma')
*/

function imagemagick2_blur($params){
	if(!$params['sigma']){
		$params['sigma']=0;
	}

  $mslfile='<blur radius="'.$params['radius'].'" sigma="'.$params['sigma'].'"/>';
    return $mslfile;
}

/*
* Charcoal an image - Params('radius','sigma')
*/

function imagemagick2_charcoal($params){
	if(!$params['sigma']){
		$params['sigma']=0;
	}
  $mslfile='<charcoal radius="'.$params['radius'].'" sigma="'.$params['sigma'].'"/>';
  return $mslfile;
}
/*
* Emboss an image - Params('radius','sigma')
*/

function imagemagick2_emboss($params){
	if(!$params['sigma']){
		$params['sigma']=0;
	}

  $mslfile='<emboss radius="'.$params['radius'].'" sigma="'.$params['sigma'].'"/>';
  return $mslfile;
}
/*
* Sharpen an image - Params('radius','sigma')
*/

function imagemagick2_sharpen($params){
if(!$params['sigma']){
		$params['sigma']=0;
	}

  $mslfile='<sharpen radius="'.$params['radius'].'" sigma="'.$params['sigma'].'"/>';
  return $mslfile;
}

/* 
* Swirl an image - Params('degrees')
*/

function imagemagick2_swirl($params){
  $mslfile='<swirl degrees="'.$params['degrees'].'"/>';
  return $mslfile;

}

/* 
* Spread an image - Params('degrees')
*/

function imagemagick2_spread($params){
  $mslfile='<spread degrees="'.$params['degrees'].'"/>';
  return $mslfile;
}

/* 
* Solarize an image - Params('threshold')
*/

function imagemagick2_solarize($params){
  $mslfile='<solarize threshold="'.$params['threshold'].'"/>';
  return $mslfile;
}
/* Some common functions flip,flop,magnify,miniify,normalize, trim */

function imagemagick2_flip(){
  $mslfile='<flip/>';
  return $mslfile;
}


function imagemagick2_flop(){
  $mslfile='<flop/>';
  return $mslfile;
}


function imagemagick2_minify(){
  $mslfile='<minify/>';
  return $mslfile;

}

function imagemagick2_magnify(){
  $mslfile='<magnify/>';
  return $mslfile;
}


function imagemagick2_normalize(){
  $mslfile='<normalize/>';
  return $mslfile;
}


function imagemagick2_trim(){
  $mslfile='<trim/>';
  return $mslfile;
}

/*
Transparent an Image - Params('color')
*/

function imagemagick2_transparent($params){
  $mslfile='<transparent color="'.$params['color'].'"/>';
  return $mslfile;
}



function _image2_escape_shell($filename) {
  if (strstr($_SERVER['SERVER_SOFTWARE'], 'Win32') || strstr($_SERVER['SERVER_SOFTWARE'], 'IIS')) {
    return '"' . addslashes($filename) . '"';
  } else {
    return escapeshellarg($filename);
  }
}

/**
 * Calls the conjure binary the mslfile.
 */
function _imagemagick2_conjure($mslcontents) {
  $conjure_path = variable_get('imagemagick_conjure', '/usr/bin/conjure');
  if (!file_exists($conjure_path)) {
    return false;
  }
  
  $mslfile=mslfile($mslcontents);
  $err = _image2_exec("$conjure_path $mslfile");

  /* After finishing the conversion delete the mslfile . Instead of cleaning up using a cron job.*/
	unlink($mslfile); 
 if ($err) {
    return false;
  }
   
  return true;
}

function _image2_exec($cmd) {
  if (substr(php_uname(), 0, 7) == "Windows"){
    if ($h = popen("start \"bla\" $cmd", "r")) {
      pclose($h);
      return true;
    } else {
      return false;
    }
  } else {
    return exec($cmd);    
  }
} 

?>
