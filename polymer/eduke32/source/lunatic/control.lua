-- Game control module for Lunatic.

local ffi = require("ffi")
local ffiC = ffi.C

local bit = require("bit")
local math = require("math")

local setmetatable = setmetatable

local error = error
local type = type

local player = player


module(...)


local lastid = { action=0, move=0, ai=0 }
local def = { action={}, move={}, ai={} }

local function forbidden() error("newindex forbidden", 2) end

AC = setmetatable({}, { __index=def.action, __newindex=forbidden })
MV = setmetatable({}, { __index=def.move, __newindex=forbidden })
AI = setmetatable({}, { __index=def.ai, __newindex=forbidden })

local function check_name(name, what, errlev)
    if (type(name)~="string" or #name > 63) then
        error("bad argument #1 to "..what..": must be a string of length <= 63", errlev+1)
    end
end

local function action_or_move(what, numargs, tab, name, ...)
    if (lastid[what] <= -(2^31)) then
        error("Too many "..what.."s defined", 3);
    end
    check_name(name, what, 3)

    local args = {...}
    if (#args > numargs) then
        error("Too many arguments passed to "..what, 3)
    end

    for i=1,#args do
        local n = args[i]
        if (type(n)~="number" or not (n >= -32768 and n <= 32767)) then
            error("bad argument #".. i+1 .." to "..what..
                  ": must be numbers in [-32768..32767]", 3)
        end
    end
    -- missing fields are initialized to 0 by ffi.new

    -- Named actions or moves have negative ids so that non-negative ones
    -- can be used as (different) placeholders for all-zero ones.
    lastid[what] = lastid[what]-1

    -- ffi.new takes either for initialization: varargs, a table with numeric
    -- indices, or a table with key-value pairs
    -- See http://luajit.org/ext_ffi_semantics.html#init_table
    tab[name] = ffi.new("const con_"..what.."_t", lastid[what], args)
end

function action(name, ...)
    action_or_move("action", 5, def.action, name, ...)
end

function move(name, ...)
    action_or_move("move", 2, def.move, name, ...)
end


local function get_action_or_move(what, val, argi)
    if (val == nil) then
        return {}  -- will init the struct to all zeros
    elseif (type(val)=="string") then
        local am = def[what][val]
        if (am==nil) then
            error("no "..what.." '"..val.."' defined", 3)
        end
        return am
    elseif (ffi.istype("con_"..what.."_t", val)) then
        return val
    end

    -- TODO: literal number actions/moves?
    error("bad argument #"..argi.." to ai: must be string or "..what, 3)
end

function ai(name, action, move, flags)
    if (lastid.ai <= -(2^31)) then
        error("Too many AIs defined", 2);
    end
    check_name(name, "ai", 2)

    lastid.ai = lastid.ai-1

    local act = get_action_or_move("action", action, 2)
    local mov = get_action_or_move("move", move, 3)

    if (flags~=nil) then
        if (type(flags)~="number" or not (flags>=0 and flags<=32767)) then
            error("bad argument #4 to ai: must be a number in [0..32767]", 2)
        end
    else
        flags = 0
    end

    def.ai[name] = ffi.new("const con_ai_t", lastid.ai, act, mov, flags)
end


--== RUNTIME CON FUNCTIONS ==--

function rotatesprite(x, y, zoom, ang, tilenum, shade, pal, orientation,
                      cx1, cy1, cx2, cy2)
    if (type(tilenum) ~= "number" or not (tilenum >= 0 and tilenum < ffiC.MAXTILES)) then
        error("bad argument #5 to rotatesprite: must be number in [0.."..ffiC.MAXTILES.."]", 2)
    end

    ffiC.rotatesprite(65536*x, 65536*y, zoom, ang, tilenum, shade, pal, bit.bor(2,orientation),
                      cx1, cy1, cx2, cy2)
end

function rnd(x)
    return (bit.rshift(ffiC.krand(), 8) >= (255-x))
end


---=== Weapon stuff


--- Helper functions (might be exported later)

local function have_weapon(ps, weap)
    return (bit.band(ps.gotweapon, bit.lshift(1, weap)) ~= 0)
end

local function have_ammo_at_max(ps, weap)
    return (ps:get_ammo_amount(weap) >= ps:get_max_ammo_amount(weap))
end

local function P_AddAmmo(ps, weap, amount)
    if (not have_ammo_at_max(ps, weap)) then
        -- NOTE: no clamping towards the bottom
        ps:set_ammo_amount(weap, math.min(curamount+amount, maxamount))
    end
end

local function P_AddWeaponAmmoCommon(ps, weap, amount)
    P_AddAmmo(ps, weap, amount)

    if (ps.curr_weapon==KNEE_WEAPON and have_weapon(weap)) then
        ffiC.P_AddWeaponMaybeSwitch(ps, weap);
    end
end


--- Exported functions

-- Non-local control flow. These ones call the original error(), not our
-- redefinition in defs.ilua.
function longjmp()
    error(false)
end

function killit()
    -- TODO: guard against deletion of player sprite?
    error(true)
end

-- The return value is true iff the ammo was at the weapon's max.
-- In that case, no action is taken.
function addammo(ps, weapon, amount)
    return have_ammo_at_max(ps, weap) or P_AddWeaponAmmoCommon(ps, weap, amount)
end

function addweapon(ps, weapon, amount)
    if (weap >= ffiC.MAX_WEAPONS+0ULL) then
        error("Invalid weapon ID "..weap, 2)
    end

    if (not have_weapon(ps, weap)) then
        ffiC.P_AddWeaponMaybeSwitch(ps, weap);
    elseif (have_ammo_at_max(ps, weap)) then
        return true
    end

    P_AddWeaponAmmoCommon(ps, weap, amount)
end
