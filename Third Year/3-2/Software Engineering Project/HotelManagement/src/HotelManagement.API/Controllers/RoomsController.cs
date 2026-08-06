using HotelManagement.Application.Interfaces;
using HotelManagement.Domain.Entities;
using Microsoft.AspNetCore.Mvc;

namespace HotelManagement.API.Controllers;

[ApiController]
[Route("api/[controller]")]

public class RoomsController : ControllerBase
{
    private readonly IRoomService _roomService;

    public RoomsController(IRoomService roomService)
    {
        _roomService = roomService;
    }

    //GET: api/rooms
    [HttpGet]
    public async Task<IActionResult> GetAllRooms()
    {
        var rooms = await _roomService.GetAllRoomsAsync();

        return Ok(rooms);
    }

    //GET: api/rooms/{id}
    [HttpGet("{id}")]
    public async Task<IActionResult> GetRoomById(int id)
    {
        var room = await _roomService.GetRoomByIdAsync(id);

        if (room == null)
        {
            return NotFound();
        }
        return Ok(room);
    }

    //POST: api/rooms
    [HttpPost]
    public async Task<IActionResult> CreateRoom(Room room)
    {
        await _roomService.AddRoomAsync(room);
        return Ok(room);
    }

    //PUT: api/rooms/{id}
    [HttpPut("{id}")]
    public async Task<IActionResult> UpdateRoom(int id, Room room)
    {
        if (id != room.Id)
        {
            return BadRequest();
        }
        await _roomService.UpdateRoomAsync(room);
        return Ok(room);
    }

    //DELETE: api/room/{id}
    [HttpDelete("{id}")]
    public async Task<IActionResult> DeleteRoom(int id)
    {
        await _roomService.DeleteRoomAsync(id);
        return NoContent();
    }
}