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
  module_load_include('object.inc', 'islandora_fedora_api');

  $object = new FedoraObject($fedora_pid);
  $object_datastreams = $object->get_datastreams();

  // Create array of dsid=>mime_type.
  foreach ($object_datastreams as $object_datastreams) {
    $display_datastreams[$object_datastreams->_dsID] = $object_datastreams->dsMIME;
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
