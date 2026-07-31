using DTOs;
using WebApp1;
using WebApp1.Data;
using WebApp1.EndPoints;

var builder = WebApplication.CreateBuilder(args);
//Adding Validation service
builder.Services.AddValidation();

//Connecting WebApp1.db database with context
var connString = "Data Source=WebApp1.db";
builder.Services.AddSqlite<WebApp1Context>(connString);

var app = builder.Build();
app.MapProductsEndPoints();
app.Run();
