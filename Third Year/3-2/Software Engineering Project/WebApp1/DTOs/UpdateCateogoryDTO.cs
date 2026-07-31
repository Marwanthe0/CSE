using System.ComponentModel.DataAnnotations;

namespace WebApp1;

public record UpdateCategoryDTO([Required] [StringLength(50)] string Name);
