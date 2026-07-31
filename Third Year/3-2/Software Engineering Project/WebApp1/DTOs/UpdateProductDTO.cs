using System.ComponentModel.DataAnnotations;

namespace WebApp1;

public record UpdateProductDTO(
    [Required][StringLength(50)] string Name,
    [Required][StringLength(20)] string Category,
    DateOnly ReleaseDate
);
