using DTOs;

namespace WebApp1.EndPoints;

public static class ProductsEndPoints
{
    const string GetProductById = "GetProduct";
    private static readonly List<ProductDTO> products =
    [
        new(1, "ball", "Sports", new DateOnly(2021, 12, 23)),
        new(2, "SmartPhone", "Electronics", new DateOnly(2023, 10, 13)),
    ];

    public static void MapProductsEndPoints(this WebApplication app)
    {
        var ProductGroup = app.MapGroup("/product");
        //GET /product
        ProductGroup.MapGet("/", () => products);

        //GET /product/id
        ProductGroup
            .MapGet(
                "/{id}",
                (int id) =>
                {
                    var product = products.Find(product => product.Id == id);
                    if (product == null)
                    {
                        return Results.NotFound("Product with this id doesn't exist");
                    }
                    return Results.Ok(product);
                }
            )
            .WithName(GetProductById);

        //POST /product
        ProductGroup.MapPost(
            "/",
            (CreateProductDTO newproduct) =>
            {
                ProductDTO product = new(
                    products.Count + 1,
                    newproduct.Name,
                    newproduct.Category,
                    newproduct.ReleaseDate
                );

                products.Add(product);

                return Results.CreatedAtRoute(GetProductById, new { id = product.Id }, product);
            }
        );

        //PUT /product/id
        ProductGroup.MapPut(
            "/{id}",
            (int id, UpdateProductDTO UpdatedProduct) =>
            {
                var index = products.FindIndex(product => product.Id == id);

                if (index == -1)
                {
                    return Results.NotFound("Product with this id doesn't exist.");
                }
                products[index] = new ProductDTO(
                    id,
                    UpdatedProduct.Name,
                    UpdatedProduct.Category,
                    UpdatedProduct.ReleaseDate
                );
                return Results.NoContent();
            }
        );

        //DELETE /product/id
        ProductGroup.MapDelete(
            "/{id}",
            (int id) =>
            {
                products.RemoveAll(product => product.Id == id);

                return Results.NoContent();
            }
        );
    }
}
