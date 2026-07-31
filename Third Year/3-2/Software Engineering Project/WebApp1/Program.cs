using DTOs;
using WebApp1;
using WebApp1.Data;
using WebApp1.EndPoints;
using WebApp1.Models;

var builder = WebApplication.CreateBuilder(args);

//Adding Validation service
builder.Services.AddValidation();
//Connecting WebApp1.db database with context
builder.AddWebapp1Db();
var app = builder.Build();
app.MapProductsEndPoints();
app.MapCategoriesEndPoints();
app.MigrateDb();
app.Run();
