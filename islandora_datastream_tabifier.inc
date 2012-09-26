<?php
/**
 * @file
 * Main include file for the islandora_datastream_tabifier.
 */

/**
 * This function will get the datastreams to make avaialable
 * for viewing when visiting the object
 *
 * @param string $fedora_pid
 *   The PID of the object
 *
 * @return array
 *   $display_datastreams: dsid=>mime_type
 *
 */
function islandora_datastream_tabifier_get_display_datastreams($fedora_pid) {
  $display_datastreams = array();

  // Get the object's datasteams.
  module_load_include('inc', 'fedora_repository', 'api/tuque');
  $Fedora_object = islandora_object_load($fedora_pid);
  foreach ($Fedora_object as $ds) {
    $display_datastreams[$ds->id] = $ds->mimeType;
  }
  return $display_datastreams;
}
/**
 * This function will get the pid of the current object being visited.
 * It relies on the drupal function request_uri()
 * It will only work on /drupal/fedora/repository/(pid)
 *
 * @return string
 *   $fedora_pid The Fedora PID of the object being visited.
 *
 */
function islandora_datastream_tabifier_get_fedora_pid() {

  /*@todo: refactor this function out use form storage or the parameters to the page instead*/
  $request_uri = request_uri();
  $fedora_pid = substr($request_uri, strrpos($request_uri, '/') + 1, strlen($request_uri));
  return urldecode($fedora_pid);
}
