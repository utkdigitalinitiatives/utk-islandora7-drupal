<?php

/**
 * Class VttConverter
 * Adopted from here: https://github.com/mantas-done/subtitles/blob/c11531b7a191b97e25235fabc804368a52326108/src/code/Converters/VttConverter.php
 *
 */

class VttConverter  {

  public function fileContentToInternalFormat($file_content)
  {
    $internal_format = array(); // array - where file content will be stored

    $blocks = explode("\n\n", trim($file_content)); // each block contains: start and end times + text

    foreach ($blocks as $block) {
      if(preg_match('/^WEBVTT.{0,}/', $block, $matches)) {
        continue;
      }

      $lines = explode("\n", $block); // separate all block lines

      if (strpos($lines[0], '-->') === false) { // first line not containing '-->', must be cue id
        unset($lines[0]); // not supporting cue id
        $lines = array_values($lines);
      }

      $times = explode(' --> ', $lines[0]);

      if (isset($lines[1])) {
        $name = static::getName($lines[1]);
      } else {
        $name = "";
      }

      $lines_array = array_map(static::fixLine(), array_slice($lines, 1)); // get all the remaining lines from block (if multiple lines of text)
      if (count($lines_array) === 0) {
        continue;
      }

      $internal_format_cue = array(
        'start' => static::vttTimeToInternal($times[0]),
        'end' => static::vttTimeToInternal($times[1]),
        'name' => $name,
        'lines' => $lines_array,
      );

      array_push($internal_format, $internal_format_cue);
    }

    return $internal_format;
  }

  public function internalFormatToFileContent(array $internal_format)
  {
    $file_content = "WEBVTT\r\n\r\n";

    foreach ($internal_format as $k => $block) {
      $start = static::internalTimeToVtt($block['start']);
      $end = static::internalTimeToVtt($block['end']);
      $lines = implode("\r\n", $block['lines']);

      $file_content .= $start . ' --> ' . $end . "\r\n";
      $file_content .= $lines . "\r\n";
      $file_content .= "\r\n";
    }

    $file_content = trim($file_content);

    return $file_content;
  }

  // ------------------------------ private --------------------------------------------------------------------------

  protected static function vttTimeToInternal($vtt_time)
  {
    $parts = explode('.', $vtt_time);

    // parts[0] could be mm:ss or hh:mm:ss format -> always use hh:mm:ss
    $parts[0] = substr_count($parts[0], ':') == 2 ? $parts[0] : '00:'.$parts[0];

    $only_seconds = strtotime("1970-01-01 {$parts[0]} UTC");
    $milliseconds = (float)('0.' . $parts[1]);

    $time = $only_seconds + $milliseconds;

    return $time;
  }

  protected static function internalTimeToVtt($internal_time)
  {
    $parts = explode('.', $internal_time); // 1.23
    $whole = $parts[0]; // 1
    $decimal = isset($parts[1]) ? substr($parts[1], 0, 3) : 0; // 23

    $srt_time = gmdate("H:i:s", floor($whole)) . '.' . str_pad($decimal, 3, '0', STR_PAD_RIGHT);

    return $srt_time;
  }

  protected static function fixLine()
  {
    return function($line) {
      // Remove name from content
      $regex_vtt_name = '/^\s*<v\s+(?<name>.*)>/';
      preg_match($regex_vtt_name, $line, $matches);
      if (array_key_exists('name', $matches)) {
        $line = preg_replace($regex_vtt_name, '', $line);
      }

      return $line;
    };
  }

  protected static function getName($line)
  {

    $regex_vtt_name = '/^\s*<v\s+(?<name>.*)>/';
    preg_match($regex_vtt_name, $line, $matches);

    $name = "";
    if (array_key_exists('name', $matches)) {
      $name = $matches['name'];
    }

    return $name;
  }

}
