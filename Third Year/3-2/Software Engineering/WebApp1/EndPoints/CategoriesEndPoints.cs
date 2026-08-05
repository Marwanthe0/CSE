using Microsoft.EntityFrameworkCore;
using WebApp1.Data;
using WebApp1.DTOs;
using WebApp1.Models;

namespace WebApp1.EndPoints
{
    public static class CategoriesEndPoints
    {
        public static void MapCategoriesEndPoints(this WebApplication app)
        {
            const string GetCategoryById = "GetCategory";
            var CategoriesGroup = app.MapGroup("/Category");
            //GET /Category
            CategoriesGroup.MapGet(
                "/",
                async (WebApp1Context dbContext) =>
                {
                    return await dbContext
                        .Categories.Select(Category => new CategoryDTO(Category.Id, Category.Name))
                        .AsNoTracking()
                        .ToListAsync();
                }
            );

            //GET /Category/{id}
            CategoriesGroup
                .MapGet(
                    "/{id}",
                    async (int id, WebApp1Context dbContext) =>
                    {
                        Category? category = await dbContext.Categories.FindAsync(id);
                        return category == null
                            ? Results.NotFound("Category with this id Doesn't Exist")
                            : Results.Ok(new CategoryDTO(category.Id, category.Name));
                    }
                )
                .WithName(GetCategoryById);

            //POST /Category
            CategoriesGroup.MapPost(
                "/",
                async (CreateCategoryDTO newCategory, WebApp1Context dbContext) =>
                {
                    Category category = new() { Name = newCategory.Name };
                    dbContext.Categories.Add(category);
                    await dbContext.SaveChangesAsync();
                    CategoryDTO categorydto = new CategoryDTO(category.Id, category.Name);
                    return Results.CreatedAtRoute(
                        GetCategoryById,
                        new { id = category.Id },
                        categorydto
                    );
                }
            );

            //PUT /Category/{id}
            CategoriesGroup.MapPut(
                "/{id}",
                async (int id, CategoryDTO newCategory, WebApp1Context dbContext) =>
                {
                    var category = await dbContext.Categories.FindAsync(id);
                    if (category == null)
                    {
                        return Results.NotFound("Category with this id doesn't Exist.");
                    }
                    category.Name = newCategory.Name;
                    await dbContext.SaveChangesAsync();
                    return Results.NoContent();
                }
            );

            //DELETE /Category/{id}
            CategoriesGroup.MapDelete(
                "/{id}",
                async (int id, WebApp1Context dbContext) =>
                {
                    await dbContext
                        .Categories.Where(category => category.Id == id)
                        .ExecuteDeleteAsync();
                    return Results.NoContent();
                }
            );
        }
    }
}
