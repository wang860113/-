<?php
$servername = "localhost";
$username = "root";
$password = "0000";
$dbname = "Test";
 
// 创建连接
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("连接失败: " . $conn->connect_error);
} 
 
$sql = "SELECT datetime, uS, pH, percent FROM data";
$result = $conn->query($sql);
 
if ($result->num_rows > 0) {
    // 输出数据
    while($row = $result->fetch_assoc()) {
        echo "datetime: " . $row["datetime"]. " uS: " . $row["uS"]. " pH:" . $row["pH"]. "percent:" . $row["percent"] ."<br>" ;
        $datetime[] = $row["datetime"];
        $uS[] = $row["datatime"];
    }
} else {
    echo "0 结果";
}
$conn->close();
?>
