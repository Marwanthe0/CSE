using Microsoft.EntityFrameworkCore;
using WebApp1.Models;

namespace WebApp1.Data
{
    public static class DataExtensions
    {
        public static void MigrateDb(this WebApplication app)
        {
            using var scope = app.Services.CreateScope();
            var dbContext = scope.ServiceProvider.GetRequiredService<WebApp1Context>();
            dbContext.Database.Migrate();
        }

        public static void AddWebapp1Db(this WebApplicationBuilder builder)
        {
            var connString = builder.Configuration.GetConnectionString("WebApp1");
            builder.Services.AddSqlite<WebApp1Context>(
                connString,
                optionsAction: options =>
                    options.UseSeeding(
                        (context, _) =>
                        {
                            if (!context.Set<Category>().Any())
                            {
                                context
                                    .Set<Category>()
                                    .AddRange(
                                        new Category { Name = "Clothing" },
                                        new Category { Name = "Electronics" },
                                        new Category { Name = "Appliance" },
                                        new Category { Name = "Tools" }
                                    );
                                context.SaveChanges();
                            }
                        }
                    )
            );
        }
    }
}
