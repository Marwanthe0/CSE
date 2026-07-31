using System.ComponentModel.DataAnnotations;
namespace WebApp1;

public record CreateProductDTO(
    [Required][StringLength(50)] string Name,
    [Required][StringLength(20)] string Category,
    DateOnly ReleaseDate
);
