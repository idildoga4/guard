using System.Collections.Generic;
using IoTSensorAPI.Models;
using Microsoft.EntityFrameworkCore;

namespace IoTSensorAPI.Data
{
    public class OracleDbContext : DbContext
    {
        public OracleDbContext(DbContextOptions<OracleDbContext> options) : base(options) { }

        public DbSet<SensorData> SensorData { get; set; }
    }
}
