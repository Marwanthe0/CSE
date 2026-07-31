using DTOs;
using Microsoft.EntityFrameworkCore;
using WebApp1.Data;
using WebApp1.Models;

namespace WebApp1.EndPoints;

public static class ProductsEndPoints
{
    const string GetProductById = "GetProduct";

    public static void MapProductsEndPoints(this WebApplication app)
    {
        var ProductGroup = app.MapGroup("/product");
        //GET /product
        ProductGroup.MapGet(
            "/",
            async (WebApp1Context dbContext) =>
            {
                return await dbContext
                    .Products.Include(product => product.Category)
                    .Select(product => new ProductSummaryDTO(
                        product.Id,
                        product.Name,
                        product.Category!.Name,
                        product.ReleaseDate
                    ))
                    .AsTracking()
                    .ToListAsync();
            }
        );

        //GET /product/id
        ProductGroup
            .MapGet(
                "/{id}",
                async (int id, WebApp1Context dbContext) =>
                {
                    var product = await dbContext.Products.FindAsync(id);
                    return product == null
                        ? Results.NotFound("Product with this id doesn't exist.")
                        : Results.Ok(
                            new ProductdetailsDTO(
                                product.Id,
                                product.Name,
                                product.CategoryId,
                                product.ReleaseDate
                            )
                        );
                }
            )
            .WithName(GetProductById);

        //POST /product
        ProductGroup.MapPost(
            "/",
            async (CreateProductDTO newproduct, WebApp1Context dbContext) =>
            {
                Product product = new()
                {
                    Name = newproduct.Name,
                    CategoryId = newproduct.CategoryId,
                    ReleaseDate = newproduct.ReleaseDate,
                };
                dbContext.Products.Add(product);
                await dbContext.SaveChangesAsync();
                ProductdetailsDTO productDTO = new(
                    product.Id,
                    product.Name,
                    product.CategoryId,
                    product.ReleaseDate
                );
                return Results.CreatedAtRoute(
                    GetProductById,
                    new { id = productDTO.Id },
                    productDTO
                );
            }
        );

        //PUT /product/id
        ProductGroup.MapPut(
            "/{id}",
            async (int id, UpdateProductDTO givenProduct, WebApp1Context dbContext) =>
            {
                var product = await dbContext.Products.FindAsync(id);
                if (product == null)
                {
                    return Results.NotFound("Product with this id doesn't exist");
                }
                product.Name = givenProduct.Name;
                product.CategoryId = givenProduct.CategoryId;
                product.ReleaseDate = givenProduct.ReleaseDate;
                await dbContext.SaveChangesAsync();

                return Results.NoContent();
            }
        );

        //DELETE /product/id
        ProductGroup.MapDelete(
            "/{id}",
            async (int id, WebApp1Context dbContext) =>
            {
                // var product = await dbContext.Products.FindAsync(id);
                // if (product is null)
                // {
                //     return Results.NotFound("Product With this Id Doesn't Exist");
                // }
                // dbContext.Products.Remove(product);
                // await dbContext.SaveChangesAsync();
                await dbContext.Products.Where(product => product.Id == id).ExecuteDeleteAsync();
                return Results.NoContent();
            }
        );
    }
}
