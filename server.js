var config = require('./config.js');
var request = require('request');

var apiKey = config.apiKey;
var url = 'https://api.nasa.gov/neo/rest/v1/feed?start_date=2016-02-10&end_date=2016-02-11&api_key='+apiKey;

//var d = new Date();
//var todayDate = d.getFullYear() + "-" + getMonthPlus(d) + "-" + getDayPlus(d);
var todayDate = '2016-02-11';
request(url,function(error, response, body){
  if (!error && response.statusCode == 200) {
    var result = JSON.parse(body);
    var nearEarthObjects = result.near_earth_objects;

    if(nearEarthObjects.length==0) {
         console.log(" neo is undefined ");
       } else{
         console.log(nearEarthObjects[todayDate].length);

         for(var i = 0; i < nearEarthObjects[todayDate].length; i++){
           var obj = nearEarthObjects[todayDate][i];
           console.log(obj.name);
           console.log(obj.close_approach_data[0].miss_distance.miles);
         }
       }
   }
});
