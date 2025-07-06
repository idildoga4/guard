CREATE TABLE SensorData (
    Id INT IDENTITY(1,1) PRIMARY KEY,
    DeviceId INT NOT NULL,
    Temperature FLOAT,
    Humidity FLOAT,
    Timestamp DATETIME
);

