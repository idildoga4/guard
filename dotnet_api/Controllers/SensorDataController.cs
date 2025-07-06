using Microsoft.AspNetCore.Mvc;
using IoTSensorAPI.Models;


namespace IoTSensorAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class SensorDataController : ControllerBase
    {
        private readonly SensorDataService _sensorDataService;
        public SensorDataController(SensorDataService sensorDataService)
        {
            _sensorDataService = sensorDataService;
        }
        [HttpPost]
        public IActionResult PostSensorData([FromBody] SensorData data)
        {
            _sensorDataService.SaveSensorData(data);
            Console.WriteLine($"Veri alındı: {data.Temperature} C, {data.Humidity} %");
            return Ok(new { message = "Veri başarıyla alınıd." });
            
        }
    }
}
