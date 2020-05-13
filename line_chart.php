<?php
$servername = "localhost";
$username = "root";
$password = "0000";
$dbname = "Test";
 
// 创建连接
$conn = new mysqli($servername, $username, $password, $dbname);
?>
<!DOCTYPE HTML>
<html>
<head>
 <meta charset="utf-8">
 <title>mySQL DATA</title>
 <script type="text/javascript" src="https://www.google.com/jsapi"></script>
  <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
 <script type="text/javascript">
 google.load("visualization", "1", {packages:["corechart"]});
 google.setOnLoadCallback(drawChart);
 function drawChart() {
     
 var data_uS = google.visualization.arrayToDataTable([
 
 ['Datetimes','uS'],
 <?php 
			//$sql = "SELECT datetime, uS FROM data order by datetime asc LIMIT ($result->num_rows)-10, 10";
            $sql = "select datetime, uS from (SELECT datetime, uS FROM data order by datetime desc limit 10)aa order by datetime";
			 $result = $conn->query($sql);
			 while($row = $result->fetch_assoc()) {
       // echo "datetime: " . $row["datetime"]. " uS: " . $row["uS"]. " pH:" . $row["pH"]. "percent:" . $row["percent"] ."<br>" ;
        echo "['".$row['datetime']."',".$row['uS']."],";
    }
			 ?> 
 
 ]);
 
  var data_pH = google.visualization.arrayToDataTable([
 
 ['Datetimes','pH'],
 <?php 
			//$sql = "SELECT datetime, pH FROM data  order by datetime asc LIMIT ($result->num_rows)-10, 10";
            $sql = "select datetime, pH from (SELECT datetime, pH FROM data order by datetime desc limit 10)aa order by datetime";
            
			 $result = $conn->query($sql);
			 while($row = $result->fetch_assoc()) {
       // echo "datetime: " . $row["datetime"]. " uS: " . $row["uS"]. " pH:" . $row["pH"]. "percent:" . $row["percent"] ."<br>" ;
        echo "['".$row['datetime']."',".$row['pH']."],";
    }
			 ?> 
 
 ]);
 
 var data_percent = google.visualization.arrayToDataTable([
 
 ['Datetimes','percent'],
 <?php 
			//$sql = "SELECT datetime, percent FROM data order by datetime asc LIMIT ($result->num_rows)-10, 10";
            $sql = "select datetime, percent from (SELECT datetime, percent FROM data order by datetime desc limit 10)aa order by datetime";
			 $result = $conn->query($sql);
			 while($row = $result->fetch_assoc()) {
       // echo "datetime: " . $row["datetime"]. " uS: " . $row["uS"]. " pH:" . $row["pH"]. "percent:" . $row["percent"] ."<br>" ;
        echo "['".$row['datetime']."',".$row['percent']."],";
    }
			 ?> 
 
 ]);
 <?php
 $conn->close();
 ?>
 var options_uS = {
 title: 'uS value',
 colors: ['Red'],
 vAxis:{
     title: 'uS/cm',
     titleTextStyle: {color:'Red',fontSize:20,italic:false}
     },
 hAxis:{
    title: 'datetime',
    titleTextStyle: {color:'Red',fontSize:20,italic:false}
    },
 pointSize:5,
 };
 var options_pH = {
 title: 'pH value',
 colors: ['blue'],
 vAxis:{
     title: 'ph',
     titleTextStyle: {color:'blue',fontSize:20,italic:false}
     },
 hAxis:{
    title: 'datetime',
    titleTextStyle: {color:'blue',fontSize:20,italic:false}
    },
 pointSize:5,

 };
 var options_percent = {
 title: 'water percent',
 colors: ['gray'],
 vAxis:{
     title: 'water %',
     titleTextStyle: {color:'gray',fontSize:20,italic:false}
     },
 hAxis:{
    title: 'datetime',
    titleTextStyle: {color:'gray',fontSize:20,italic:false}
    },
 pointSize:5,
 };
 var chart_uS = new google.visualization.LineChart(document.getElementById('curve_chart_uS'));
 var chart_pH = new google.visualization.LineChart(document.getElementById('curve_chart_pH'));
 var chart_percent = new google.visualization.LineChart(document.getElementById('curve_chart_percent'));
 chart_uS.draw(data_uS,options_uS);
 chart_pH.draw(data_pH,options_pH);
 chart_percent.draw(data_percent,options_percent);
 }
	
    </script>
 
</head>
<body>
 <div class="jumbotron text-center">
 <div id="curve_chart_uS" style="width: 1800px; height: 400px"></div>
 <div id="curve_chart_pH" style="width: 1800px; height: 400px"></div>
  <div id="curve_chart_percent" style="width: 1800px; height: 400px"></div>
 </div>
 
</body>
</html>
