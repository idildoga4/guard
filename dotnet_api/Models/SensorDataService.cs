using Microsoft.Data.SqlClient;
using IoTSensorAPI.Models;

public class SensorDataService
{
    private readonly IConfiguration _configuration;

    public SensorDataService(IConfiguration configuration)
    {
        _configuration = configuration;
    }

    public void SaveSensorData(SensorData data)
    {
        string connStr = _configuration.GetConnectionString("SqlServerDb");

        using (var conn = new SqlConnection(connStr))
        {
            conn.Open();

            using (var cmd = conn.CreateCommand())
            {
                cmd.CommandText = @"INSERT INTO SensorData (DeviceId, Temperature, Humidity, Timestamp)
                                    VALUES (@deviceId, @temp, @humidity, @timestamp)";

                cmd.Parameters.AddWithValue("@deviceId", data.DeviceId);
                cmd.Parameters.AddWithValue("@temp", data.Temperature);
                cmd.Parameters.AddWithValue("@humidity", data.Humidity);
                cmd.Parameters.AddWithValue("@timestamp", data.Timestamp);

                cmd.ExecuteNonQuery();
            }
        }
    }
}
