var config = require('./config.js');
var request = require('request');

var apiKey = config.apiKey;
var url = 'https://api.nasa.gov/neo/rest/v1/feed?start_date=2016-02-10&end_date=2016-02-11&api_key=' + apiKey;

//var d = new Date();
//var todayDate = d.getFullYear() + "-" + getMonthPlus(d) + "-" + getDayPlus(d);
var todayDate = '2016-02-11';

var brightness = [];
var velocity = [];
var diameter = [];

request(url, function(error, response, body) {
  if (!error && response.statusCode == 200) {
    var result = JSON.parse(body);
    var nearEarthObjects = result.near_earth_objects;

    if (nearEarthObjects[todayDate].length == 0) {
      console.log(" neo is undefined ");
    } else {
      console.log("number of astroieds: " + nearEarthObjects[todayDate].length);

      for (var i = 0; i < nearEarthObjects[todayDate].length; i++) {
        var obj = nearEarthObjects[todayDate][i];
        var b = parseFloat(obj.absolute_magnitude_h);
        brightness.push(b);
        var v = parseFloat(obj.close_approach_data[0].relative_velocity.kilometers_per_second);
        velocity.push(Math.round(100*v));
        var d = parseFloat(obj.estimated_diameter.feet.estimated_diameter_max);
        diameter.push(d.toFixed(2));
      }

      birghtness = mapArray(brightness,65535,5000);
      velocity = mapArray(velocity,150,40);
      console.log("brightness: " + brightness);
      console.log("velocity: " + velocity);
      console.log("diameter: " + diameter);
      /*
      for(var i = 0; i < nearEarthObjects[todayDate].length; i++){
        var obj = nearEarthObjects[todayDate][i];
        console.log("name: "+obj.name);
        console.log("miss_distance: "+obj.close_approach_data[0].miss_distance.miles +" miles");
        console.log("estimated_diameter min: "+obj.estimated_diameter.miles.estimated_diameter_min+" miles");
        console.log("estimated_diameter max: "+obj.estimated_diameter.miles.estimated_diameter_max+" miles");
        console.log("is_potentially_hazardous_asteroid: "+obj.is_potentially_hazardous_asteroid);
        console.log("relative_velocity: "+obj.close_approach_data[0].relative_velocity.miles_per_hour+"  miles_per_hour");
        console.log("absolute_magnitude_h: "+obj.absolute_magnitude_h);
      }
      */

    }
  }
});


function mapArray(thisArray, max, min){
  var originalMax = thisArray[0];
  var originalMin = thisArray[0];
  for (var i = 0; i < thisArray.length; i++) {
    if (thisArray[i] > originalMax) {
      originalMax = thisArray[i];
    }
    if (thisArray[i] < originalMin) {
      originalMin = thisArray[i];
    }
  }
  var ratio = (max-min) / (originalMax - originalMin);
  for (var i = 0; i < thisArray.length; i++) {
    thisArray[i]= (thisArray[i]-originalMin)*ratio+min;
    thisArray[i]=Math.round(thisArray[i]);
  }

  return thisArray;
}
